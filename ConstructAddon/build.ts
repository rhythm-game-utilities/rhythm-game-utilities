import { copyFile, mkdir, readFile, rename, writeFile } from 'node:fs/promises';

import { Project, SourceFile, Type } from 'ts-morph';

import AdmZip from 'adm-zip';

const JAVASCRIPT_PACKAGE_DIR = '../JavaScriptPackages/core';

const project = new Project();
const sourceFile = project.addSourceFileAtPath(
  `${JAVASCRIPT_PACKAGE_DIR}/dist/index.d.ts`
);

function getParamType(type: Type): string {
  if (type.isString() || type.isStringLiteral()) return 'string';
  if (type.isNumber() || type.isBoolean()) return 'number';

  return 'string';
}

function getReturnType(type: Type): string {
  if (type.isNumber() || type.isBoolean()) return 'number';

  return 'string';
}

async function generateExpressionsFile(sourceFile: SourceFile) {
  await writeFile(
    'c3addon/c3runtime/expressions.js',
    `import { RhythmGameUtilities } from './instance.js';

export default {
${sourceFile
  .getFunctions()
  .map(method => {
    return `  ${method.getName()}(${method
      .getParameters()
      .map(p => p.getName())
      .join(', ')}) {
    if (!RhythmGameUtilities) {
      return ${method.getReturnType().isNumber() || method.getReturnType().isBoolean() ? -1 : "''"};
    }
    return RhythmGameUtilities.${method.getName()}(${method
      .getParameters()
      .map(p => p.getName())
      .join(', ')});
  }`;
  })
  .join(',\n')}
};
`
  );
}

async function generateInstanceFile() {
  const moduleContents = await readFile(
    `${JAVASCRIPT_PACKAGE_DIR}/dist/module.mjs`,
    'utf8'
  );

  await writeFile(
    'c3addon/c3runtime/instance.js',
    `${moduleContents.replace('export default Module;', '')}

export let RhythmGameUtilities;

export default class RhythmGameUtilitiesInstance
  extends globalThis.ISDKInstanceBase
{
  constructor(opts) {
    super(opts);

    this._loadModule();
  }

  async _loadModule() {
    RhythmGameUtilities = await Module();
  }
}
`
  );
}

async function generateLocaleFile(sourceFile: SourceFile) {
  await writeFile(
    'c3addon/lang/en-US.json',
    `${JSON.stringify(
      {
        languageTag: 'en-US',
        fileDescription: 'Strings for Rhythm Game Utilities',
        text: {
          plugins: {
            rhythmgameutilities: {
              name: 'RhythmGameUtilities',
              description:
                'A collection of utilities for creating rhythm games.',
              'help-url': 'https://rhythmgameutilities.com/',
              properties: {},
              aceCategories: {
                general: 'General'
              },
              actions: {},
              conditions: {},
              expressions: sourceFile.getFunctions().reduce(
                (previousMethods, currentMethod) => ({
                  ...previousMethods,
                  [currentMethod.getName()]: {
                    'translated-name': currentMethod.getName(),
                    description: currentMethod.getName(),
                    params: currentMethod.getParameters().reduce(
                      (prevParams, currParam) => ({
                        ...prevParams,
                        [currParam.getName()]: {
                          name: currParam.getName(),
                          desc: currParam.getName()
                        }
                      }),
                      {}
                    )
                  }
                }),
                {}
              )
            }
          }
        }
      },
      null,
      2
    )}\n`
  );
}

async function generateAcesFile(sourceFile: SourceFile) {
  await writeFile(
    'c3addon/aces.json',
    `${JSON.stringify(
      {
        general: {
          actions: [],
          conditions: [],
          expressions: sourceFile.getFunctions().map(method => ({
            id: method.getName(),
            expressionName: method.getName(),
            highlight: false,
            returnType: getReturnType(method.getReturnType()),
            params: method.getParameters().map(p => ({
              id: p.getName(),
              type: getParamType(p.getType())
            }))
          }))
        }
      },
      null,
      2
    )}\n`
  );
}

async function createAddonDist(filename: string, version: string = 'v1') {
  await mkdir('dist', { recursive: true });

  const zip = new AdmZip();

  const outputFilePath = `dist/${filename}_${version}.zip`;
  const fileOutputFilePath = `dist/${filename}_${version}.c3addon`;

  zip.addLocalFolder('./c3addon');

  zip.writeZip(outputFilePath);

  await rename(outputFilePath, fileOutputFilePath);

  console.log(`Created ${fileOutputFilePath} successfully`);
}

await generateExpressionsFile(sourceFile);
await generateInstanceFile();
await generateLocaleFile(sourceFile);
await generateAcesFile(sourceFile);
await createAddonDist('ConstructAddonTemplate');
