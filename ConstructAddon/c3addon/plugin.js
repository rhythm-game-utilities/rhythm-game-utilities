const SDK = globalThis.SDK;

const PLUGIN_ID = 'RhythmGameUtilities';
const PLUGIN_CATEGORY = 'general';

SDK.Plugins.RhythmGameUtilities = class RhythmGameUtilitiesPlugin extends (
  SDK.IPluginBase
) {
  constructor() {
    super(PLUGIN_ID);

    SDK.Lang.PushContext('plugins.' + PLUGIN_ID.toLowerCase());

    this._info.SetName(globalThis.lang('.name'));
    this._info.SetDescription(globalThis.lang('.description'));
    this._info.SetCategory(PLUGIN_CATEGORY);
    this._info.SetAuthor('Scott Doxey');
    this._info.SetHelpUrl(globalThis.lang('.help-url'));
    this._info.SetIsSingleGlobal(true);
    this._info.SetRuntimeModuleMainScript('c3runtime/main.js');

    SDK.Lang.PopContext();
  }
};

SDK.Plugins.RhythmGameUtilities.Register(
  PLUGIN_ID,
  SDK.Plugins.RhythmGameUtilities
);
