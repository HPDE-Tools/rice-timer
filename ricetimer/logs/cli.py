from datetime import datetime
from pathlib import Path

import click
import click_spinner
import toml

from ricetimer import DATA_PATH
from ricetimer.logs.format import vbo
from ricetimer.logs.ingest import ingest_log_lines
from ricetimer.logs.processing import tabulate_with_profile


@click.command()
@click.option('-o', '--output', 'output_file', type=click.File(mode='w', encoding='utf8'))
@click.option('-p', '--profile')
@click.argument('src_dir', type=click.Path(exists=True, file_okay=False, path_type=Path))
def export(src_dir: Path, output_file: Path, profile):
    profile_path = resolve_profile_path(profile)
    try:
        profile = toml.load(profile_path)
    except FileNotFoundError:
        click.echo(
            f'cannot find profile {profile} -- full path: {profile_path}')
        profile = None
    except ValueError as e:
        click.echo(f'error parsing profile {profile}: {e}')
        profile = None

    splits = find_log_files(src_dir)
    click.echo(f'found {len(splits)} log files in: {src_dir}')
    click.echo('loading log...')
    with click_spinner.spinner():
        log_events = ingest_log_lines(files_to_lines(splits))
    click.echo(f'{len(log_events)} events loaded.')
    click.echo('converting to table...')
    with click_spinner.spinner():
        table = tabulate_with_profile(log_events, profile)
    click.echo('writing output file...')
    with click_spinner.spinner():
        vbo.write_vbo(table, output_file)
    click.echo('done!')


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
