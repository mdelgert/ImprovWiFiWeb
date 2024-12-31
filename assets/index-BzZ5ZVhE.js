const __vite__mapDeps=(i,m=__vite__mapDeps,d=(m.f||(m.f=["assets/install-dialog-L0madDvw.js","assets/styles-CPGZSYgv.js","assets/index-BsgLK8vy.js"])))=>i.map(i=>d[i]);
(function(){const t=document.createElement("link").relList;if(t&&t.supports&&t.supports("modulepreload"))return;for(const e of document.querySelectorAll('link[rel="modulepreload"]'))r(e);new MutationObserver(e=>{for(const i of e)if(i.type==="childList")for(const s of i.addedNodes)s.tagName==="LINK"&&s.rel==="modulepreload"&&r(s)}).observe(document,{childList:!0,subtree:!0});function n(e){const i={};return e.integrity&&(i.integrity=e.integrity),e.referrerPolicy&&(i.referrerPolicy=e.referrerPolicy),e.crossOrigin==="use-credentials"?i.credentials="include":e.crossOrigin==="anonymous"?i.credentials="omit":i.credentials="same-origin",i}function r(e){if(e.ep)return;e.ep=!0;const i=n(e);fetch(e.href,i)}})();const w="modulepreload",E=function(o){return"/ImprovWiFiWeb/"+o},p={},f=function(t,n,r){let e=Promise.resolve();if(n&&n.length>0){document.getElementsByTagName("link");const s=document.querySelector("meta[property=csp-nonce]"),a=(s==null?void 0:s.nonce)||(s==null?void 0:s.getAttribute("nonce"));e=Promise.allSettled(n.map(l=>{if(l=E(l),l in p)return;p[l]=!0;const u=l.endsWith(".css"),g=u?'[rel="stylesheet"]':"";if(document.querySelector(`link[href="${l}"]${g}`))return;const d=document.createElement("link");if(d.rel=u?"stylesheet":w,u||(d.as="script"),d.crossOrigin="",d.href=l,a&&d.setAttribute("nonce",a),document.head.appendChild(d),u)return new Promise((y,v)=>{d.addEventListener("load",y),d.addEventListener("error",()=>v(new Error(`Unable to preload CSS for ${l}`)))})}))}function i(s){const a=new Event("vite:preloadError",{cancelable:!0});if(a.payload=s,window.dispatchEvent(a),!a.defaultPrevented)throw s}return e.then(s=>{for(const a of s||[])a.status==="rejected"&&i(a.reason);return t().catch(i)})},m=async o=>{f(()=>import("./install-dialog-L0madDvw.js"),__vite__mapDeps([0,1]));let t;try{t=await navigator.serial.requestPort()}catch(r){if(r.name==="NotFoundError"){f(()=>import("./index-BsgLK8vy.js"),__vite__mapDeps([2,1])).then(e=>e.openNoPortPickedDialog(()=>m(o)));return}alert(`Error: ${r.message}`);return}if(!t)return;try{await t.open({baudRate:115200})}catch(r){alert(r.message);return}const n=document.createElement("ewt-install-dialog");n.port=t,n.manifestPath=o.manifest||o.getAttribute("manifest"),n.overrides=o.overrides,n.addEventListener("closed",()=>{t.close()},{once:!0}),document.body.appendChild(n)};class c extends HTMLElement{connectedCallback(){if(this.renderRoot)return;if(this.renderRoot=this.attachShadow({mode:"open"}),!c.isSupported||!c.isAllowed){this.toggleAttribute("install-unsupported",!0),this.renderRoot.innerHTML=c.isAllowed?"<slot name='unsupported'>Your browser does not support installing things on ESP devices. Use Google Chrome or Microsoft Edge.</slot>":"<slot name='not-allowed'>You can only install ESP devices on HTTPS websites or on the localhost.</slot>";return}this.toggleAttribute("install-supported",!0);const t=document.createElement("slot");t.addEventListener("click",async r=>{r.preventDefault(),m(this)}),t.name="activate";const n=document.createElement("button");if(n.innerText="Connect",t.append(n),"adoptedStyleSheets"in Document.prototype&&"replaceSync"in CSSStyleSheet.prototype){const r=new CSSStyleSheet;r.replaceSync(c.style),this.renderRoot.adoptedStyleSheets=[r]}else{const r=document.createElement("style");r.innerText=c.style,this.renderRoot.append(r)}this.renderRoot.append(t)}}c.isSupported="serial"in navigator;c.isAllowed=window.isSecureContext;c.style=`
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
  }`;customElements.define("esp-web-install-button",c);const S="https://api.github.com/repos/mdelgert/ImprovWiFiWeb/releases",h=document.getElementById("firmware-select"),b=document.getElementById("install-button");async function P(){try{const o=await fetch(S);if(!o.ok)throw new Error(`GitHub API error: ${o.statusText}`);const t=await o.json();L(t)}catch(o){console.error("Failed to fetch releases:",o)}}function L(o){o.forEach(t=>{const n=t.tag_name,r=`firmware/${n}.json`,e=document.createElement("option");e.value=r,e.textContent=`${n}`,h.appendChild(e)}),o.length>0&&b.setAttribute("manifest",`firmware/${o[0].tag_name}.json`)}h.addEventListener("change",o=>{const t=o.target.value;b.setAttribute("manifest",t)});P();export{f as _};
