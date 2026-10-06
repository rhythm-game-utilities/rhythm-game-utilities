export let RhythmGameUtilities;

export default class RhythmGameUtilitiesInstance
  extends globalThis.ISDKInstanceBase
{
  constructor(opts) {
    super(opts);

    this._wasmInstance = null;

    this._loadModule();
  }

  async _loadModule() {
    const moduleScript = await import('../lib/module.js');

    RhythmGameUtilities = await moduleScript.default();
  }
}
