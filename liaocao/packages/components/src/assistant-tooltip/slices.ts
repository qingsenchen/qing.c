import { $ctx } from '@milkdown/utils'
import type { Mark } from '@milkdown/prose/model'
import { html } from 'atomico'
import { withMeta } from '../__internal__/meta'

export interface AssistantState {
  mode: 'preview' | 'edit'
}

const defaultState: AssistantState = {
  mode: 'preview',
}

export const assistantState = $ctx({ ...defaultState }, 'assistantStateCtx')

withMeta(assistantState, {
  displayName: 'State<assistant>',
  group: 'Assistant',
})

export interface AssistantAPI {
  addLink: (from: number, to: number) => void
  editLink: (mark: Mark, from: number, to: number) => void
  removeLink: (from: number, to: number) => void
}

const defaultAPI: AssistantAPI = {
  addLink: () => {},
  editLink: () => {},
  removeLink: () => {},
}

export const assistantAPI = $ctx({ ...defaultAPI }, 'assistantAPICtx')

withMeta(assistantState, {
  displayName: 'API<assistant>',
  group: 'Assistant',
})

export interface AssistantConfig {
  linkIcon: () => ReturnType<typeof html>
  editButton: () => ReturnType<typeof html>
  confirmButton: () => ReturnType<typeof html>
  removeButton: () => ReturnType<typeof html>
  onCopyLink: (link: string) => void
  inputPlaceholder: string
}

const defaultConfig: AssistantConfig = {
  linkIcon: () => '🔗',
  editButton: () => '✎',
  removeButton: () => '⌫',
  confirmButton: () => html`Confirm ⏎`,
  onCopyLink: () => {},
  inputPlaceholder: 'Paste link...',
}

export const assistantConfig = $ctx({
  ...defaultConfig,
}, 'assistantConfigCtx')

withMeta(assistantState, {
  displayName: 'Config<assistant>',
  group: 'Assistant',
})
