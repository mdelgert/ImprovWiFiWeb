const __vite__mapDeps=(i,m=__vite__mapDeps,d=(m.f||(m.f=["assets/install-dialog-DpnwXHQW.js","assets/styles-CPGZSYgv.js","assets/index-BsgLK8vy.js"])))=>i.map(i=>d[i]);
(function(){const t=document.createElement("link").relList;if(t&&t.supports&&t.supports("modulepreload"))return;for(const e of document.querySelectorAll('link[rel="modulepreload"]'))o(e);new MutationObserver(e=>{for(const s of e)if(s.type==="childList")for(const r of s.addedNodes)r.tagName==="LINK"&&r.rel==="modulepreload"&&o(r)}).observe(document,{childList:!0,subtree:!0});function n(e){const s={};return e.integrity&&(s.integrity=e.integrity),e.referrerPolicy&&(s.referrerPolicy=e.referrerPolicy),e.crossOrigin==="use-credentials"?s.credentials="include":e.crossOrigin==="anonymous"?s.credentials="omit":s.credentials="same-origin",s}function o(e){if(e.ep)return;e.ep=!0;const s=n(e);fetch(e.href,s)}})();const y="modulepreload",v=function(l){return"/ImprovWiFiWeb/"+l},p={},f=function(t,n,o){let e=Promise.resolve();if(n&&n.length>0){document.getElementsByTagName("link");const r=document.querySelector("meta[property=csp-nonce]"),c=(r==null?void 0:r.nonce)||(r==null?void 0:r.getAttribute("nonce"));e=Promise.allSettled(n.map(a=>{if(a=v(a),a in p)return;p[a]=!0;const u=a.endsWith(".css"),h=u?'[rel="stylesheet"]':"";if(document.querySelector(`link[href="${a}"]${h}`))return;const d=document.createElement("link");if(d.rel=u?"stylesheet":y,u||(d.as="script"),d.crossOrigin="",d.href=a,c&&d.setAttribute("nonce",c),document.head.appendChild(d),u)return new Promise((b,g)=>{d.addEventListener("load",b),d.addEventListener("error",()=>g(new Error(`Unable to preload CSS for ${a}`)))})}))}function s(r){const c=new Event("vite:preloadError",{cancelable:!0});if(c.payload=r,window.dispatchEvent(c),!c.defaultPrevented)throw r}return e.then(r=>{for(const c of r||[])c.status==="rejected"&&s(c.reason);return t().catch(s)})},m=async l=>{f(()=>import("./install-dialog-DpnwXHQW.js"),__vite__mapDeps([0,1]));let t;try{t=await navigator.serial.requestPort()}catch(o){if(o.name==="NotFoundError"){f(()=>import("./index-BsgLK8vy.js"),__vite__mapDeps([2,1])).then(e=>e.openNoPortPickedDialog(()=>m(l)));return}alert(`Error: ${o.message}`);return}if(!t)return;try{await t.open({baudRate:115200})}catch(o){alert(o.message);return}const n=document.createElement("ewt-install-dialog");n.port=t,n.manifestPath=l.manifest||l.getAttribute("manifest"),n.overrides=l.overrides,n.addEventListener("closed",()=>{t.close()},{once:!0}),document.body.appendChild(n)};class i extends HTMLElement{connectedCallback(){if(this.renderRoot)return;if(this.renderRoot=this.attachShadow({mode:"open"}),!i.isSupported||!i.isAllowed){this.toggleAttribute("install-unsupported",!0),this.renderRoot.innerHTML=i.isAllowed?"<slot name='unsupported'>Your browser does not support installing things on ESP devices. Use Google Chrome or Microsoft Edge.</slot>":"<slot name='not-allowed'>You can only install ESP devices on HTTPS websites or on the localhost.</slot>";return}this.toggleAttribute("install-supported",!0);const t=document.createElement("slot");t.addEventListener("click",async o=>{o.preventDefault(),m(this)}),t.name="activate";const n=document.createElement("button");if(n.innerText="Connect",t.append(n),"adoptedStyleSheets"in Document.prototype&&"replaceSync"in CSSStyleSheet.prototype){const o=new CSSStyleSheet;o.replaceSync(i.style),this.renderRoot.adoptedStyleSheets=[o]}else{const o=document.createElement("style");o.innerText=i.style,this.renderRoot.append(o)}this.renderRoot.append(t)}}i.isSupported="serial"in navigator;i.isAllowed=window.isSecureContext;i.style=`
  button {
    position: relative;
    cursor: pointer;
    font-size: 14px;
    font-weight: 500;
    padding: 10px 24px;
    color: var(--esp-tools-button-text-color, #fff);
    background-color: var(--esp-tools-button-color, #03a9f4);
    border: none;
    border-radius: var(--esp-tools-button-border-radius, 9999px);
  }
  button::before {
    content: " ";
    position: absolute;
    top: 0;
    bottom: 0;
    left: 0;
    right: 0;
    opacity: 0.2;
    border-radius: var(--esp-tools-button-border-radius, 9999px);
  }
  button:hover::before {
    background-color: rgba(255,255,255,.8);
  }
  button:focus {
    outline: none;
  }
  button:focus::before {
    background-color: white;
  }
  button:active::before {
    background-color: grey;
  }
  :host([active]) button {
    color: rgba(0, 0, 0, 0.38);
    background-color: rgba(0, 0, 0, 0.12);
    box-shadow: none;
    cursor: unset;
    pointer-events: none;
  }
  .hidden {
    display: none;
  }`;customElements.define("esp-web-install-button",i);export{f as _};
