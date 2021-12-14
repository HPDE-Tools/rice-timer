from datetime import datetime
from io import TextIOBase
from pathlib import Path

import click
import click_spinner
import toml

from ricetimer import DATA_PATH
from ricetimer.logs import format
from ricetimer.logs.ingest import ingest_log_lines
from ricetimer.logs.processing import tabulate_with_profile


@click.group()
def export():
    pass


@export.command()
@click.option('-o', '--output', 'output_file', type=click.File(mode='w', encoding='utf8'))
@click.option('-p', '--profile', 'profile_name')
@click.argument('src_dir', type=click.Path(exists=True, file_okay=False, path_type=Path))
def vbo(src_dir: Path, output_file: Path, profile_name):
    profile_path = resolve_profile_path(profile_name)
    try:
        profile = toml.load(profile_path)
    except FileNotFoundError:
        click.echo(
            f'cannot find profile {profile_name} -- full path: {profile_path}')
        profile = None
    except ValueError as e:
        click.echo(f'error parsing profile {profile_name}: {e}')
        profile = None

    log_events = load_events(src_dir)
    click.echo('converting to table...')
    with click_spinner.spinner():
        table = tabulate_with_profile(log_events, profile)
    click.echo('writing output file...')
    with click_spinner.spinner():
        format.vbo.write_vbo(table, output_file)
    click.echo('done!')


@export.command()
@click.option('-o', '--output', 'output_file', type=click.File(mode='w', encoding='utf8'))
@click.option('-h/-H', '--header/--noheader', 'write_header', default=True)
@click.argument('src_dir', type=click.Path(exists=True, file_okay=False, path_type=Path))
def can(src_dir: Path, output_file: TextIOBase, write_header: bool):
    if write_header:
        output_file.write('timestamp,id,dlc,data\n')
    count = 0
    log_events = load_events(src_dir)
    for typestr, timestamp, content in log_events:
        if typestr != 'c':
            continue
        id, dlc, data = content
        # hack: ID within 11-bit range will be considered standard; otherwise extended
        id_str = f'{id:03X}' if id <= 0x7ff else f'{id:08X}'
        output_file.write(f'{timestamp.timestamp():.3f},{id_str},{dlc},{data.hex().upper()}\n')
        count += 1
    click.echo(f'{count} CAN frames written.')


def load_events(src_dir: Path):
    splits = find_log_files(src_dir)
    click.echo(f'found {len(splits)} log files in: {src_dir}')
    click.echo('loading log...')
    with click_spinner.spinner():
        log_events = ingest_log_lines(files_to_lines(splits))
    click.echo(f'{len(log_events)} events loaded.')
    return log_events


def resolve_profile_path(name: str):
    if not name:
        return ""
    rel = Path(name)
    if rel.is_absolute():
        return rel
    return (DATA_PATH / 'profile' / rel).with_suffix('.toml')


def find_log_files(dir: Path):
    return sorted([p for p in dir.glob('**/*.log')
                   if p.stem.isnumeric()],
                  key=lambda p: int(p.stem))


def files_to_lines(files):
    for file in files:
        with open(file, 'r') as f:
            yield from map(str.rstrip, f)
