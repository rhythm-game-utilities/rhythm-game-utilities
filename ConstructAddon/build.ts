import { copyFile, mkdir, readFile, rename, writeFile } from 'node:fs/promises';

import { Project, SourceFile, Type } from 'ts-morph';

import AdmZip from 'adm-zip';

const JAVASCRIPT_PACKAGE_DIR = '../JavaScriptPackage';

const project = new Project();
const sourceFile = project.addSourceFileAtPath(
  `${JAVASCRIPT_PACKAGE_DIR}/dist/index.d.ts`
);

const packageFile = JSON.parse(
  await readFile(`${JAVASCRIPT_PACKAGE_DIR}/package.json`, 'utf8')
);

async function copyFilesFromJavaScriptPackage() {
  await mkdir('dist/c3addon/lib/', { recursive: true });

  await Promise.all(
    ['module.mjs', 'module.wasm'].map(async file => {
      await copyFile(
        `${JAVASCRIPT_PACKAGE_DIR}/dist/${file}`,
        `dist/c3addon/lib/${file}`
      );
    })
  );
}

async function generateAddonFile(packageFile: any) {
  await mkdir('dist/c3addon/', { recursive: true });

  await writeFile(
    'dist/c3addon/addon.json',
    JSON.stringify(
      {
        'is-single-global': true,
        'is-c3-addon': true,
        'sdk-version': 2,
        type: 'plugin',
        id: 'RhythmGameUtilities',
        name: 'RhythmGameUtilities',
        version: packageFile.version,
        author: packageFile.authors[0].name,
        website: packageFile.homepage,
        documentation: packageFile.homepage,
        description: packageFile.description,
        'c3runtime-scripts': [
          'c3runtime/plugin.js',
          'c3runtime/type.js',
          'c3runtime/instance.js'
        ],
        'editor-scripts': ['plugin.js', 'type.js', 'instance.js'],
        'file-list': [
          'c3runtime/main.js',
          'c3runtime/plugin.js',
          'c3runtime/type.js',
          'c3runtime/instance.js',
          'c3runtime/conditions.js',
          'c3runtime/actions.js',
          'c3runtime/expressions.js',
          'lang/en-US.json',
          'aces.json',
          'addon.json',
          'icon.svg',
          'plugin.js',
          'type.js',
          'instance.js',
          'lib/module.mjs',
          'lib/module.wasm'
        ]
      },
      null,
      2
    )
  );
}

function getParamType(type: Type): string {
  if (type.isString() || type.isStringLiteral()) return 'string';
  if (type.isNumber() || type.isBoolean()) return 'number';

  return 'string';
}

function getReturnType(type: Type): string {
  if (type.isNumber() || type.isBoolean()) return 'number';

  return 'string';
}

async function generateAcesFile(sourceFile: SourceFile) {
  await mkdir('dist/c3addon/', { recursive: true });

  await writeFile(
    'dist/c3addon/aces.json',
    JSON.stringify(
      {
        general: {
          actions: [],
          conditions: [],
          expressions: sourceFile.getFunctions().map(method => ({
            id: method.getName(),
            scriptName: method.getName(),
            highlight: false,
            expressionName: method.getName(),
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
    )
  );
}

async function generateActionsFile() {
  await mkdir('dist/c3addon/c3runtime/', { recursive: true });

  await writeFile(
    'dist/c3addon/c3runtime/actions.js',
    `globalThis.C3.Plugins.RhythmGameUtilities.Acts = {};
`
  );
}

async function generateConditionsFile() {
  await mkdir('dist/c3addon/c3runtime/', { recursive: true });

  await writeFile(
    'dist/c3addon/c3runtime/conditions.js',
    `globalThis.C3.Plugins.RhythmGameUtilities.Cnds = {};
`
  );
}

async function generateExpressionsFile(sourceFile: SourceFile) {
  await mkdir('dist/c3addon/c3runtime/', { recursive: true });

  await writeFile(
    'dist/c3addon/c3runtime/expressions.js',
    `globalThis.C3.Plugins.RhythmGameUtilities.Exps = {
${sourceFile
  .getFunctions()
  .map(method => {
    return `  ${method.getName()}(inst, ${method
      .getParameters()
      .map(p => p.getName())
      .join(', ')}) {
    return inst.${method.getName()}(${method
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

async function generateInstanceFile(sourceFile: SourceFile) {
  await mkdir('dist/c3addon/c3runtime/', { recursive: true });

  await writeFile(
    'dist/c3addon/instance.js',
    `const SDK = globalThis.SDK;

const PLUGIN_CLASS = SDK.Plugins.RhythmGameUtilities;

PLUGIN_CLASS.Instance = class RhythmGameUtilitiesInstance extends (
  SDK.IInstanceBase
) {
  constructor(sdkType, inst) {
    super(sdkType, inst);
  }

  Release() {
  }

  OnCreate() {
  }
};
`
  );

  await writeFile(
    'dist/c3addon/c3runtime/instance.js',
    `globalThis.C3.Plugins.RhythmGameUtilities.Instance = class RhythmGameUtilitiesInstance extends (
  globalThis.ISDKInstanceBase
) {
  constructor(opts) {
    super(opts);

    this._wasmInstance = null;
    this._isReady = false;
  }

  async _OnCreate() {
    console.log('_OnCreate');

    try {
      const wasmUrl = await this._runtime.assets.getProjectFileUrl('lib/module.wasm');
      const mjsUrl = await this._runtime.assets.getProjectFileUrl('lib/module.mjs');

      const moduleScript = await import(mjsUrl);
      const RhythmGameUtilitiesModule = moduleScript.default;

      this._wasmInstance = await RhythmGameUtilitiesModule({
        locateFile(path) {
          if (path.endsWith('.wasm')) {
            return wasmUrl;
          }
          return path;
        }
      });

      this._isReady = true;
      console.log('WASM loaded successfully inside C3 Runtime!');
    } catch (err) {
      console.error('Failed to load WASM in C3 Runtime:', err);
    }
  }

  _Release() {
    super._release();
  }

${sourceFile
  .getFunctions()
  .map(method => {
    let returnString = 'return output;';

    if (method.getReturnType().isBoolean()) {
      returnString = 'return output ? 1 : 0';
    }

    if (method.getReturnType().isObject()) {
      returnString = 'return JSON.stringify(output);';
    }

    return `  ${method.getName()}(${method
      .getParameters()
      .map(p => p.getName())
      .join(', ')}) {
    if (!this._isReady) return ${method.getReturnType().isNumber() || method.getReturnType().isBoolean() ? 0 : "''"};
    const output = this._wasmInstance.${method.getName()}(${method
      .getParameters()
      .map(p => p.getName())
      .join(', ')});
    ${returnString}
  }`;
  })
  .join('\n')}
};
`
  );
}

async function generateMainFile() {
  await mkdir('dist/c3addon/c3runtime/', { recursive: true });

  await writeFile(
    'dist/c3addon/c3runtime/main.js',
    `import "./plugin.js";
import "./type.js";
import "./instance.js";
import "./conditions.js";
import "./actions.js";
import "./expressions.js";
`
  );
}

async function generateLocaleFile(sourceFile: SourceFile, packageFile: any) {
  await mkdir('dist/c3addon/lang/', { recursive: true });

  await writeFile(
    'dist/c3addon/lang/en-US.json',
    JSON.stringify(
      {
        languageTag: 'en-US',
        fileDescription: 'Strings for Rhythm Game Utilities',
        text: {
          plugins: {
            rhythmgameutilities: {
              name: 'RhythmGameUtilities',
              description: packageFile.description,
              'help-url': packageFile.homepage,
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
    )
  );
}

async function createAddonDist() {
  const zip = new AdmZip();

  const outputFilePath = 'dist/rhythm_game_utilities_v1.zip';
  const fileOutputFilePath = 'dist/rhythm_game_utilities_v1.c3addon';

  zip.addLocalFolder('./dist/c3addon');

  zip.writeZip(outputFilePath);

  rename(outputFilePath, fileOutputFilePath);
  console.log(`Created ${fileOutputFilePath} successfully`);
}

async function generatePluginFile(packageFile: any) {
  await mkdir('dist/c3addon/c3runtime', { recursive: true });

  await writeFile(
    'dist/c3addon/c3runtime/plugin.js',
    `globalThis.C3.Plugins.RhythmGameUtilities = class RhythmGameUtilities extends (
  globalThis.ISDKPluginBase
) {};
`
  );

  await writeFile(
    'dist/c3addon/plugin.js',
    `const SDK = globalThis.SDK;

const PLUGIN_ID = 'RhythmGameUtilities';

const PLUGIN_CLASS =
  (SDK.Plugins.RhythmGameUtilities = class RhythmGameUtilitiesTemplate  extends (
    SDK.IPluginBase
  ) {
    constructor() {
      super(PLUGIN_ID);

      SDK.Lang.PushContext('plugins.' + PLUGIN_ID.toLowerCase());

      this._info.SetName(globalThis.lang('.name'));
      this._info.SetDescription(globalThis.lang('.description'));
      this._info.SetCategory('general');
      this._info.SetAuthor('${packageFile.authors?.[0]?.name ?? ''}');
      this._info.SetHelpUrl(globalThis.lang('.help-url'));

      this._info.SetRuntimeModuleMainScript("c3runtime/main.js");
      this._info.SetIsSingleGlobal(true);

      this._info.AddFileDependency({
        filename: "lib/module.wasm",
        type: "copy-to-output",
        fileType: "application/wasm"
      });

      this._info.AddFileDependency({
        filename: "lib/module.mjs",
        type: "copy-to-output",
        fileType: "text/javascript"
      });

      SDK.Lang.PushContext(".properties");
      this._info.SetProperties([]);
      SDK.Lang.PopContext();
      SDK.Lang.PopContext();
    }
  });

PLUGIN_CLASS.Register(PLUGIN_ID, PLUGIN_CLASS);
`
  );
}

async function generateTypeFile(packageFile: any) {
  await mkdir('dist/c3addon/c3runtime/', { recursive: true });

  await writeFile(
    'dist/c3addon/c3runtime/type.js',
    `globalThis.C3.Plugins.RhythmGameUtilities.Type = class RhythmGameUtilitiesType extends (
  globalThis.ISDKObjectTypeBase
) {};
`
  );
  await writeFile(
    'dist/c3addon/type.js',
    `const SDK = globalThis.SDK;

const PLUGIN_CLASS = SDK.Plugins.RhythmGameUtilities;

PLUGIN_CLASS.Type = class RhythmGameUtilitiesType extends SDK.ITypeBase {
  constructor(objectType) {
    super(objectType);
  }

  _OnCreate() {
  }
};
`
  );
}

async function copyIconFile() {
  await mkdir('dist/c3addon/', { recursive: true });

  await copyFile('../avatar.svg', 'dist/c3addon/icon.svg');
}

await copyFilesFromJavaScriptPackage();

await generateActionsFile();
await generateConditionsFile();
await generateExpressionsFile(sourceFile);
await generateInstanceFile(sourceFile);
await generateMainFile();
await generatePluginFile(packageFile);
await generateTypeFile(packageFile);

await generateAddonFile(packageFile);
await generateAcesFile(sourceFile);
await generateLocaleFile(sourceFile, packageFile);

await copyIconFile();

await createAddonDist();
