import type { MilkdownPlugin } from '@milkdown/ctx'
import { assistantAPI, assistantConfig, assistantState } from './slices'
import { assistantEditTooltip } from './tooltips'

export * from './slices'
export * from './configure'
export * from './tooltips'

export const assistantPlugin: MilkdownPlugin[] = [assistantState, assistantAPI, assistantConfig, assistantEditTooltip ].flat()
