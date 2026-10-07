#!/usr/bin/env node

import { EOL } from 'node:os';

import { dirname, extname, join, resolve } from 'node:path';

import { fileURLToPath } from 'node:url';

import { readFile, writeFile } from 'node:fs/promises';

import updateNotifier from 'update-notifier';

import parseCmdArgs from 'parse-cmd-args';

import RhythmGameUtilities from '@rhythm-game-utilities/core';

import type { Difficulty } from '@rhythm-game-utilities/core';

export const DIFFICULTIES = ['Easy', 'Medium', 'Hard', 'Expert'] as const;

const helpDocs = `Usage: rhythm-game-utilities <path> [options]

Options:

 -h, --help             Display this help message.
 -v, --version          Display the current installed version.
 -n, --notes            Output song notes.
 -d, --difficulty       Song difficulty. Required to get notes for .chart files. (${DIFFICULTIES.join(', ')})
 -r, --resolution       Output song resolution.
 -t, --tempo            Output tempo changes.
 -s, --time-signature   Output time signature changes.
 -o, --output           File to save output to. Defaults to stdout.
`;

const args = parseCmdArgs(null, {
  requireUserInput: true
});

const showHelp = Boolean(args.flags['-h'] || args.flags['--help'] || false);
const showVersion = Boolean(
  args.flags['-v'] || args.flags['--version'] || false
);

const outputNotes = String(args.flags['-n'] || args.flags['--notes'] || '');

const inputDifficulty = String(
  args.flags['-d'] || args.flags['--difficulty'] || 'Easy'
);

const outputResolutions = String(
  args.flags['-r'] || args.flags['--resolution'] || ''
);
const outputTempoChanges = String(
  args.flags['-t'] || args.flags['--tempo'] || ''
);
const outputTimeSignatureChanges = String(
  args.flags['-s'] || args.flags['--time-signature'] || ''
);

const outputPath = String(args.flags['-o'] || args.flags['--output'] || '');

const pkgPath = resolve(
  join(dirname(fileURLToPath(import.meta.url)), '../'),
  'package.json'
);

const pkg = JSON.parse(await readFile(pkgPath, 'utf8'));

const [input] = args.inputs;

updateNotifier({ pkg }).notify();

if (showVersion) {
  process.stdout.write(`${pkg.version}${EOL}`);

  process.exit();
}

if (!input || showHelp) {
  process.stdout.write(`${helpDocs}${EOL}`);

  process.exit();
}

const extension = extname(input);

let output: any;

if (extension.endsWith('chart')) {
  const contents = await readFile(input, 'utf8');

  const difficulty = (
    (DIFFICULTIES as readonly string[]).includes(inputDifficulty)
      ? inputDifficulty
      : DIFFICULTIES[0]
  ) as Difficulty;

  if (outputNotes) {
    output = RhythmGameUtilities.ReadNotesFromChartData(contents, difficulty);
  } else if (outputResolutions) {
    output = RhythmGameUtilities.ReadResolutionFromChartData(contents);
  } else if (outputTempoChanges) {
    output = RhythmGameUtilities.ReadTempoChangesFromChartData(contents);
  } else if (outputTimeSignatureChanges) {
    output =
      RhythmGameUtilities.ReadTimeSignatureChangesFromChartData(contents);
  }
} else if (extension.endsWith('mid')) {
  const contents = await readFile(input);

  if (outputNotes) {
    output = RhythmGameUtilities.ReadNotesFromMidiData(contents);
  } else if (outputResolutions) {
    output = RhythmGameUtilities.ReadResolutionFromMidiData(contents);
  } else if (outputTempoChanges) {
    output = RhythmGameUtilities.ReadTempoChangesFromMidiData(contents);
  } else if (outputTimeSignatureChanges) {
    output = RhythmGameUtilities.ReadTimeSignatureChangesFromMidiData(contents);
  }
}

if (outputPath) {
  writeFile(outputPath, `${JSON.stringify(output, null, 2)}${EOL}`);
} else {
  process.stdout.write(`${JSON.stringify(output, null, 2)}${EOL}`);
}
