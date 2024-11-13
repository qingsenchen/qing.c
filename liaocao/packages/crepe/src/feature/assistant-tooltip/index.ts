import { configureAssistantTooltip, assistantConfig, assistantPlugin } from '@milkdown/kit/component/assistant-tooltip'
import type { DefineFeature, Icon } from '../shared'
import { enterIcon, robot1Icon, editIcon, removeIcon } from '../../icons'

interface AssistantTooltipConfig {
  linkIcon: Icon
  editButton: Icon
  removeButton: Icon
  confirmButton: Icon
  inputPlaceholder: string
  onCopyLink: (link: string) => void
}

export type AssistantTooltipFeatureConfig = Partial<AssistantTooltipConfig>

export const defineFeature: DefineFeature<AssistantTooltipFeatureConfig> = (editor, config) => {
  editor
    .config(configureAssistantTooltip)
    .config((ctx) => {
      ctx.update(assistantConfig.key, prev => ({
        ...prev,
        linkIcon: config?.linkIcon ?? (() => robot1Icon),
        editButton: config?.editButton ?? (() => editIcon),
        removeButton: config?.removeButton ?? (() => removeIcon),
        confirmButton: config?.confirmButton ?? (() => enterIcon),
        inputPlaceholder: config?.inputPlaceholder ?? 'Ask AI...',
        onCopyLink: config?.onCopyLink ?? (() => {}),
      }))
    })
    .use(assistantPlugin)
}
