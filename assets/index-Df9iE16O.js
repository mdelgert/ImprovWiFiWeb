const __vite__mapDeps=(i,m=__vite__mapDeps,d=(m.f||(m.f=["assets/install-dialog-28H-HNrD-BwzGi9go.js","assets/styles-QAqj_a9t-C3XZZdT-.js","assets/index-drxht7Uc-BOjdh_UR.js"])))=>i.map(i=>d[i]);
(function(){const t=document.createElement("link").relList;if(t&&t.supports&&t.supports("modulepreload"))return;for(const e of document.querySelectorAll('link[rel="modulepreload"]'))o(e);new MutationObserver(e=>{for(const i of e)if(i.type==="childList")for(const s of i.addedNodes)s.tagName==="LINK"&&s.rel==="modulepreload"&&o(s)}).observe(document,{childList:!0,subtree:!0});function r(e){const i={};return e.integrity&&(i.integrity=e.integrity),e.referrerPolicy&&(i.referrerPolicy=e.referrerPolicy),e.crossOrigin==="use-credentials"?i.credentials="include":e.crossOrigin==="anonymous"?i.credentials="omit":i.credentials="same-origin",i}function o(e){if(e.ep)return;e.ep=!0;const i=r(e);fetch(e.href,i)}})();const w="modulepreload",E=function(n){return"/ImprovWiFiWeb/"+n},p={},f=function(t,r,o){let e=Promise.resolve();if(r&&r.length>0){document.getElementsByTagName("link");const s=document.querySelector("meta[property=csp-nonce]"),c=(s==null?void 0:s.nonce)||(s==null?void 0:s.getAttribute("nonce"));e=Promise.allSettled(r.map(l=>{if(l=E(l),l in p)return;p[l]=!0;const u=l.endsWith(".css"),g=u?'[rel="stylesheet"]':"";if(document.querySelector(`link[href="${l}"]${g}`))return;const d=document.createElement("link");if(d.rel=u?"stylesheet":w,u||(d.as="script"),d.crossOrigin="",d.href=l,c&&d.setAttribute("nonce",c),document.head.appendChild(d),u)return new Promise((y,v)=>{d.addEventListener("load",y),d.addEventListener("error",()=>v(new Error(`Unable to preload CSS for ${l}`)))})}))}function i(s){const c=new Event("vite:preloadError",{cancelable:!0});if(c.payload=s,window.dispatchEvent(c),!c.defaultPrevented)throw s}return e.then(s=>{for(const c of s||[])c.status==="rejected"&&i(c.reason);return t().catch(i)})},m=async n=>{let t;f(()=>import("./install-dialog-28H-HNrD-BwzGi9go.js"),__vite__mapDeps([0,1]));try{t=await navigator.serial.requestPort()}catch(o){return o.name==="NotFoundError"?void f(()=>import("./index-drxht7Uc-BOjdh_UR.js"),__vite__mapDeps([2,1])).then(e=>e.openNoPortPickedDialog(()=>m(n))):void alert(`Error: ${o.message}`)}if(!t)return;try{await t.open({baudRate:115200})}catch(o){return void alert(o.message)}const r=document.createElement("ewt-install-dialog");r.port=t,r.manifestPath=n.manifest||n.getAttribute("manifest"),r.overrides=n.overrides,r.addEventListener("closed",()=>{t.close()},{once:!0}),document.body.appendChild(r)};class a extends HTMLElement{connectedCallback(){if(this.renderRoot)return;if(this.renderRoot=this.attachShadow({mode:"open"}),!a.isSupported||!a.isAllowed)return this.toggleAttribute("install-unsupported",!0),void(this.renderRoot.innerHTML=a.isAllowed?"<slot name='unsupported'>Your browser does not support installing things on ESP devices. Use Google Chrome or Microsoft Edge.</slot>":"<slot name='not-allowed'>You can only install ESP devices on HTTPS websites or on the localhost.</slot>");this.toggleAttribute("install-supported",!0);const t=document.createElement("slot");t.addEventListener("click",async o=>{o.preventDefault(),m(this)}),t.name="activate";const r=document.createElement("button");if(r.innerText="CONNECT",t.append(r),"adoptedStyleSheets"in Document.prototype&&"replaceSync"in CSSStyleSheet.prototype){const o=new CSSStyleSheet;o.replaceSync(a.style),this.renderRoot.adoptedStyleSheets=[o]}else{const o=document.createElement("style");o.innerText=a.style,this.renderRoot.append(o)}this.renderRoot.append(t)}}a.isSupported="serial"in navigator,a.isAllowed=window.isSecureContext,a.style=`
  button {
    position: relative;
    cursor: pointer;
    font-size: 14px;
    padding: 8px 28px;
    color: var(--esp-tools-button-text-color, #fff);
    background-color: var(--esp-tools-button-color, #03a9f4);
    border: none;
    border-radius: 4px;
    box-shadow: 0 2px 2px 0 rgba(0,0,0,.14), 0 3px 1px -2px rgba(0,0,0,.12), 0 1px 5px 0 rgba(0,0,0,.2);
  }
  button::before {
    content: " ";
    position: absolute;
    top: 0;
    bottom: 0;
    left: 0;
    right: 0;
    opacity: 0.2;
    border-radius: 4px;
  }
  button:hover {
    box-shadow: 0 4px 8px 0 rgba(0,0,0,.14), 0 1px 7px 0 rgba(0,0,0,.12), 0 3px 1px -1px rgba(0,0,0,.2);
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
  improv-wifi-launch-button {
    display: block;
    margin-top: 16px;
  }
  .hidden {
    display: none;
  }`,customElements.define("esp-web-install-button",a);const x="https://api.github.com/repos/mdelgert/ImprovWiFiWeb/releases",h=document.getElementById("firmware-select"),b=document.getElementById("install-button");async function S(){try{const n=await fetch(x);if(!n.ok)throw new Error(`GitHub API error: ${n.statusText}`);const t=await n.json();P(t)}catch(n){console.error("Failed to fetch releases:",n)}}function P(n){n.forEach(t=>{const r=t.tag_name,o=`firmware/${r}.json`,e=document.createElement("option");e.value=o,e.textContent=`${r}`,h.appendChild(e)}),n.length>0&&b.setAttribute("manifest",`firmware/${n[0].tag_name}.json`)}h.addEventListener("change",n=>{const t=n.target.value;b.setAttribute("manifest",t)});S();export{f as _};
