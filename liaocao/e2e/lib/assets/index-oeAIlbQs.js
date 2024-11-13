import{P as j,a as S,M as U,j as D,k as R,$ as z,l as V,i as A}from"./utils-kAulCAqd.js";var E=200,u=function(){};u.prototype.append=function(e){return e.length?(e=u.from(e),!this.length&&e||e.length<E&&this.leafAppend(e)||this.length<E&&e.leafPrepend(this)||this.appendInner(e)):this};u.prototype.prepend=function(e){return e.length?u.from(e).append(this):this};u.prototype.appendInner=function(e){return new W(this,e)};u.prototype.slice=function(e,t){return e===void 0&&(e=0),t===void 0&&(t=this.length),e>=t?u.empty:this.sliceInner(Math.max(0,e),Math.min(this.length,t))};u.prototype.get=function(e){if(!(e<0||e>=this.length))return this.getInner(e)};u.prototype.forEach=function(e,t,n){t===void 0&&(t=0),n===void 0&&(n=this.length),t<=n?this.forEachInner(e,t,n,0):this.forEachInvertedInner(e,t,n,0)};u.prototype.map=function(e,t,n){t===void 0&&(t=0),n===void 0&&(n=this.length);var s=[];return this.forEach(function(r,p){return s.push(e(r,p))},t,n),s};u.from=function(e){return e instanceof u?e:e&&e.length?new H(e):u.empty};var H=function(i){function e(n){i.call(this),this.values=n}i&&(e.__proto__=i),e.prototype=Object.create(i&&i.prototype),e.prototype.constructor=e;var t={length:{configurable:!0},depth:{configurable:!0}};return e.prototype.flatten=function(){return this.values},e.prototype.sliceInner=function(s,r){return s==0&&r==this.length?this:new e(this.values.slice(s,r))},e.prototype.getInner=function(s){return this.values[s]},e.prototype.forEachInner=function(s,r,p,l){for(var a=r;a<p;a++)if(s(this.values[a],l+a)===!1)return!1},e.prototype.forEachInvertedInner=function(s,r,p,l){for(var a=r-1;a>=p;a--)if(s(this.values[a],l+a)===!1)return!1},e.prototype.leafAppend=function(s){if(this.length+s.length<=E)return new e(this.values.concat(s.flatten()))},e.prototype.leafPrepend=function(s){if(this.length+s.length<=E)return new e(s.flatten().concat(this.values))},t.length.get=function(){return this.values.length},t.depth.get=function(){return 0},Object.defineProperties(e.prototype,t),e}(u);u.empty=new H([]);var W=function(i){function e(t,n){i.call(this),this.left=t,this.right=n,this.length=t.length+n.length,this.depth=Math.max(t.depth,n.depth)+1}return i&&(e.__proto__=i),e.prototype=Object.create(i&&i.prototype),e.prototype.constructor=e,e.prototype.flatten=function(){return this.left.flatten().concat(this.right.flatten())},e.prototype.getInner=function(n){return n<this.left.length?this.left.get(n):this.right.get(n-this.left.length)},e.prototype.forEachInner=function(n,s,r,p){var l=this.left.length;if(s<l&&this.left.forEachInner(n,s,Math.min(r,l),p)===!1||r>l&&this.right.forEachInner(n,Math.max(s-l,0),Math.min(this.length,r)-l,p+l)===!1)return!1},e.prototype.forEachInvertedInner=function(n,s,r,p){var l=this.left.length;if(s>l&&this.right.forEachInvertedInner(n,s-l,Math.max(r,l)-l,p+l)===!1||r<l&&this.left.forEachInvertedInner(n,Math.min(s,l),r,p)===!1)return!1},e.prototype.sliceInner=function(n,s){if(n==0&&s==this.length)return this;var r=this.left.length;return s<=r?this.left.slice(n,s):n>=r?this.right.slice(n-r,s-r):this.left.slice(n,r).append(this.right.slice(0,s-r))},e.prototype.leafAppend=function(n){var s=this.right.leafAppend(n);if(s)return new e(this.left,s)},e.prototype.leafPrepend=function(n){var s=this.left.leafPrepend(n);if(s)return new e(s,this.right)},e.prototype.appendInner=function(n){return this.left.depth>=Math.max(this.right.depth,n.depth)+1?new e(this.left,new e(this.right,n)):new e(this,n)},e}(u);const Z=500;class m{constructor(e,t){this.items=e,this.eventCount=t}popEvent(e,t){if(this.eventCount==0)return null;let n=this.items.length;for(;;n--)if(this.items.get(n-1).selection){--n;break}let s,r;t&&(s=this.remapping(n,this.items.length),r=s.maps.length);let p=e.tr,l,a,h=[],c=[];return this.items.forEach((o,f)=>{if(!o.step){s||(s=this.remapping(n,f+1),r=s.maps.length),r--,c.push(o);return}if(s){c.push(new g(o.map));let d=o.step.map(s.slice(r)),w;d&&p.maybeStep(d).doc&&(w=p.mapping.maps[p.mapping.maps.length-1],h.push(new g(w,void 0,void 0,h.length+c.length))),r--,w&&s.appendMap(w,r)}else p.maybeStep(o.step);if(o.selection)return l=s?o.selection.map(s.slice(r)):o.selection,a=new m(this.items.slice(0,n).append(c.reverse().concat(h)),this.eventCount-1),!1},this.items.length,0),{remaining:a,transform:p,selection:l}}addTransform(e,t,n,s){let r=[],p=this.eventCount,l=this.items,a=!s&&l.length?l.get(l.length-1):null;for(let c=0;c<e.steps.length;c++){let o=e.steps[c].invert(e.docs[c]),f=new g(e.mapping.maps[c],o,t),d;(d=a&&a.merge(f))&&(f=d,c?r.pop():l=l.slice(0,l.length-1)),r.push(f),t&&(p++,t=void 0),s||(a=f)}let h=p-n.depth;return h>Q&&(l=J(l,h),p-=h),new m(l.append(r),p)}remapping(e,t){let n=new U;return this.items.forEach((s,r)=>{let p=s.mirrorOffset!=null&&r-s.mirrorOffset>=e?n.maps.length-s.mirrorOffset:void 0;n.appendMap(s.map,p)},e,t),n}addMaps(e){return this.eventCount==0?this:new m(this.items.append(e.map(t=>new g(t))),this.eventCount)}rebased(e,t){if(!this.eventCount)return this;let n=[],s=Math.max(0,this.items.length-t),r=e.mapping,p=e.steps.length,l=this.eventCount;this.items.forEach(f=>{f.selection&&l--},s);let a=t;this.items.forEach(f=>{let d=r.getMirror(--a);if(d==null)return;p=Math.min(p,d);let w=r.maps[d];if(f.step){let G=e.steps[d].invert(e.docs[d]),k=f.selection&&f.selection.map(r.slice(a+1,d));k&&l++,n.push(new g(w,G,k))}else n.push(new g(w))},s);let h=[];for(let f=t;f<p;f++)h.push(new g(r.maps[f]));let c=this.items.slice(0,s).append(h).append(n),o=new m(c,l);return o.emptyItemCount()>Z&&(o=o.compress(this.items.length-n.length)),o}emptyItemCount(){let e=0;return this.items.forEach(t=>{t.step||e++}),e}compress(e=this.items.length){let t=this.remapping(0,e),n=t.maps.length,s=[],r=0;return this.items.forEach((p,l)=>{if(l>=e)s.push(p),p.selection&&r++;else if(p.step){let a=p.step.map(t.slice(n)),h=a&&a.getMap();if(n--,h&&t.appendMap(h,n),a){let c=p.selection&&p.selection.map(t.slice(n));c&&r++;let o=new g(h.invert(),a,c),f,d=s.length-1;(f=s.length&&s[d].merge(o))?s[d]=f:s.push(o)}}else p.map&&n--},this.items.length,0),new m(u.from(s.reverse()),r)}}m.empty=new m(u.empty,0);function J(i,e){let t;return i.forEach((n,s)=>{if(n.selection&&e--==0)return t=s,!1}),i.slice(t)}class g{constructor(e,t,n,s){this.map=e,this.step=t,this.selection=n,this.mirrorOffset=s}merge(e){if(this.step&&e.step&&!e.selection){let t=e.step.merge(this.step);if(t)return new g(t.getMap().invert(),t,this.selection)}}}class v{constructor(e,t,n,s,r){this.done=e,this.undone=t,this.prevRanges=n,this.prevTime=s,this.prevComposition=r}}const Q=20;function X(i,e,t,n){let s=t.getMeta(y),r;if(s)return s.historyState;t.getMeta(B)&&(i=new v(i.done,i.undone,null,0,-1));let p=t.getMeta("appendedTransaction");if(t.steps.length==0)return i;if(p&&p.getMeta(y))return p.getMeta(y).redo?new v(i.done.addTransform(t,void 0,n,M(e)),i.undone,_(t.mapping.maps[t.steps.length-1]),i.prevTime,i.prevComposition):new v(i.done,i.undone.addTransform(t,void 0,n,M(e)),null,i.prevTime,i.prevComposition);if(t.getMeta("addToHistory")!==!1&&!(p&&p.getMeta("addToHistory")===!1)){let l=t.getMeta("composition"),a=i.prevTime==0||!p&&i.prevComposition!=l&&(i.prevTime<(t.time||0)-n.newGroupDelay||!Y(t,i.prevRanges)),h=p?C(i.prevRanges,t.mapping):_(t.mapping.maps[t.steps.length-1]);return new v(i.done.addTransform(t,a?e.selection.getBookmark():void 0,n,M(e)),m.empty,h,t.time,l??i.prevComposition)}else return(r=t.getMeta("rebased"))?new v(i.done.rebased(t,r),i.undone.rebased(t,r),C(i.prevRanges,t.mapping),i.prevTime,i.prevComposition):new v(i.done.addMaps(t.mapping.maps),i.undone.addMaps(t.mapping.maps),C(i.prevRanges,t.mapping),i.prevTime,i.prevComposition)}function Y(i,e){if(!e)return!1;if(!i.docChanged)return!0;let t=!1;return i.mapping.maps[0].forEach((n,s)=>{for(let r=0;r<e.length;r+=2)n<=e[r+1]&&s>=e[r]&&(t=!0)}),t}function _(i){let e=[];return i.forEach((t,n,s,r)=>e.push(s,r)),e}function C(i,e){if(!i)return null;let t=[];for(let n=0;n<i.length;n+=2){let s=e.map(i[n],1),r=e.map(i[n+1],-1);s<=r&&t.push(s,r)}return t}function L(i,e,t,n){let s=M(e),r=y.get(e).spec.config,p=(n?i.undone:i.done).popEvent(e,s);if(!p)return;let l=p.selection.resolve(p.transform.doc),a=(n?i.done:i.undone).addTransform(p.transform,e.selection.getBookmark(),r,s),h=new v(n?a:p.remaining,n?p.remaining:a,null,0,-1);t(p.transform.setSelection(l).setMeta(y,{redo:n,historyState:h}).scrollIntoView())}let P=!1,K=null;function M(i){let e=i.plugins;if(K!=e){P=!1,K=e;for(let t=0;t<e.length;t++)if(e[t].spec.historyPreserveItems){P=!0;break}}return P}const y=new j("history"),B=new j("closeHistory");function q(i={}){return i={depth:i.depth||100,newGroupDelay:i.newGroupDelay||500},new S({key:y,state:{init(){return new v(m.empty,m.empty,null,0,-1)},apply(e,t,n){return X(t,n,e,i)}},config:i,props:{handleDOMEvents:{beforeinput(e,t){let n=t.inputType,s=n=="historyUndo"?N:n=="historyRedo"?$:null;return s?(t.preventDefault(),s(e.state,e.dispatch)):!1}}}})}const N=(i,e)=>{let t=y.getState(i);return!t||t.done.eventCount==0?!1:(e&&L(t,i,e,!1),!0)},$=(i,e)=>{let t=y.getState(i);return!t||t.undone.eventCount==0?!1:(e&&L(t,i,e,!0),!0)};function I(i,e){return Object.assign(i,{meta:{package:"@milkdown/plugin-history",...e}}),i}const T=D("Undo",()=>()=>N);I(T,{displayName:"Command<undo>"});const x=D("Redo",()=>()=>$);I(x,{displayName:"Command<redo>"});const O=R({},"historyProviderConfig");I(O,{displayName:"Ctx<historyProviderConfig>"});const F=z(i=>q(i.get(O.key)));I(F,{displayName:"Ctx<historyProviderPlugin>"});const b=V("historyKeymap",{Undo:{shortcuts:"Mod-z",command:i=>{const e=i.get(A);return()=>e.call(T.key)}},Redo:{shortcuts:["Mod-y","Shift-Mod-z"],command:i=>{const e=i.get(A);return()=>e.call(x.key)}}});I(b.ctx,{displayName:"KeymapCtx<history>"});I(b.shortcuts,{displayName:"Keymap<history>"});const te=[O,F,b,T,x].flat();export{te as h};