import plugin from './plugin.js';
import type from './type.js';
import instance from './instance.js';
import conditions from './conditions.js';
import actions from './actions.js';
import expressions from './expressions.js';

const C3 = globalThis.C3;

C3.Plugins.RhythmGameUtilities = plugin;
C3.Plugins.RhythmGameUtilities.Acts = actions;
C3.Plugins.RhythmGameUtilities.Cnds = conditions;
C3.Plugins.RhythmGameUtilities.Exps = expressions;
C3.Plugins.RhythmGameUtilities.Instance = instance;
C3.Plugins.RhythmGameUtilities.Type = type;

globalThis.RhythmGameUtilities = expressions;
