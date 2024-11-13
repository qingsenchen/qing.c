import type { Ctx } from '@milkdown/ctx'
import { TextSelection } from '@milkdown/prose/state'
import type { PluginView } from '@milkdown/prose/state'
import type { Mark } from '@milkdown/prose/model'
import type { EditorView } from '@milkdown/prose/view'
import { AssistantProvider } from '@liaocao/plugin-assistant'
import { editorViewCtx } from '@milkdown/core'
import { posToDOMRect } from '@milkdown/prose'
import { assistantConfig, assistantState } from '../slices'
import { AssistantEditComponent } from './edit-component'

interface Data {
  from: number
  to: number
  mark: Mark | null
}

const defaultData: Data = {
  from: -1,
  to: -1,
  mark: null,
}

export class AssistantEdit implements PluginView {
  #content = new AssistantEditComponent()
  #provider: AssistantProvider
  #data: Data = { ...defaultData }
  

  constructor(readonly ctx: Ctx, view: EditorView) {
    this.#provider = new AssistantProvider({
      content: this.#content,
      debounce: 0,
      shouldShow: () => false,
    })
    this.#provider.onHide = () => {
      this.#content.update().catch((e) => {
        throw e
      })
      view.dom.focus({ preventScroll: true })
    }
    this.#provider.update(view)
    this.#content.onConfirm = this.#confirmEdit
    this.#content.onCancel = this.#reset
  }

  #reset = () => {
    this.#provider.hide()
    this.ctx.update(assistantState.key, state => ({
      ...state,
      mode: 'preview' as const,
    }))
    this.#data = { ...defaultData }
  }

  #confirmEdit = (prompt: string) => {
    const view = this.ctx.get(editorViewCtx)
    const { state } = view
    const { selection } = state
    if (!(selection instanceof TextSelection))
      return
    const { from, to } = this.#data
    const selectedText = state.doc.cut(from, to).textContent

    console.log('confirmEdit=> propmt:', prompt, ', selection:', selectedText);

    this.#reset()
  }

  #enterEditMode = (value: string, from: number, to: number) => {
    const config = this.ctx.get(assistantConfig.key)
    this.#content.config = config
    this.#content.src = value
    this.ctx.update(assistantState.key, state => ({
      ...state,
      mode: 'edit' as const,
    }))

    const view = this.ctx.get(editorViewCtx)
  
    view.dispatch(view.state.tr.setSelection(TextSelection.create(view.state.doc, from, to)))

    this.#provider.show({
      getBoundingClientRect: () => posToDOMRect(view, 0, to),
    })
    requestAnimationFrame(() => {
      this.#content.querySelector('input')?.focus()
    })
  }

  update = (view: EditorView) => {
    const { state } = view
    const { selection } = state
    if (!(selection instanceof TextSelection))
      return
    const { from, to } = selection
    if (from === this.#data.from && to === this.#data.to)
      return

    this.#reset()
  }

  destroy = () => {
    this.#provider.destroy()
    this.#content.remove()
  }

  addLink = (from: number, to: number) => {
    this.#data = {
      from,
      to,
      mark: null,
    }
    this.#enterEditMode('', from, to)
  }

  editLink = (mark: Mark, from: number, to: number) => {
    this.#data = {
      from,
      to,
      mark,
    }
    this.#enterEditMode(mark.attrs.href, from, to)
  }

  removeLink = (from: number, to: number) => {
    //const view = this.ctx.get(editorViewCtx)
    console.log('removeLink', from, to);
    this.#reset()
  }
}
