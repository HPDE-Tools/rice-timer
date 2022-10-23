from datetime import datetime
import logging
from pathlib import Path

import click
import click_spinner
import coloredlogs

import ricetimer.logs.cli

coloredlogs.install(level='INFO')


@click.group()
def main():
    pass


main.add_command(ricetimer.logs.cli.export)


if __name__ == "__main__":
    main()
