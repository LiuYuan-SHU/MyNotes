(function(){/* 
 
 Copyright The Closure Library Authors. 
 SPDX-License-Identifier: Apache-2.0 
*/ 
'use strict';/* 
 
 SPDX-License-Identifier: Apache-2.0 
*/ 
function f(a,b,d){a.addEventListener&&a.addEventListener(b,d,!1)};function g(a,b,d){if(Array.isArray(b))for(var c=0;c<b.length;c++)g(a,String(b[c]),d);else null!=b&&d.push(a+(""===b?"":"="+encodeURIComponent(String(b))))};function h(a=document){return a.createElement("img")};function k(a,b){a.google_image_requests||(a.google_image_requests=[]);const d=h(a.document);d.src=b;a.google_image_requests.push(d)};function l(a=null){return a&&"22"===a.getAttribute("data-jc")?a:document.querySelector('[data-jc="22"]')};var m=document,n=window;function p(a){return"undefined"!==typeof a}function q(a){f(m,a.h,()=>{if(m[a.g])a.i&&(a.i=!1,a.j=Date.now(),r(a,0));else{if(-1!==a.j){const b=Date.now()-a.j;0<b&&(a.j=-1,r(a,1,b))}r(a,3)}})}function t(a){f(n,"click",b=>{a.handleClick(b)})} 
function r(a,b,d=0){var c={gqid:a.m,qqid:a.o};0===b&&(c["return"]=0);1===b&&(c["return"]=1,c.timeDelta=d);2===b&&(c.bgload=1);3===b&&(c.fg=1);b=[];for(var e in c)g(e,c[e],b);k(n,a.l+"&label=window_focus&"+b.join("&"));if(!(.01<Math.random())){a=l(document.currentScript);a=`https://${"pagead2.googlesyndication.com"}/pagead/gen_204?id=jca&jc=${22}&version=${a&&a.getAttribute("data-jc-version")||"unknown"}&sample=${.01}`;c=window;if(e=c.navigator)e=c.navigator.userAgent,e=/Chrome/.test(e)&&!/Edge/.test(e)? 
!0:!1;e&&c.navigator.sendBeacon?c.navigator.sendBeacon(a):k(c,a)}} 
var v=class{constructor(){var a=u["gws-id"],b=u["qem-id"];this.l=u.url;this.m=a;this.o=b;this.i=!1;a=p(m.hidden)?{g:"hidden",h:"visibilitychange"}:p(m.mozHidden)?{g:"mozHidden",h:"mozvisibilitychange"}:p(m.msHidden)?{g:"msHidden",h:"msvisibilitychange"}:p(m.webkitHidden)?{g:"webkitHidden",h:"webkitvisibilitychange"}:{g:"hidden",h:"visibilitychange"};this.g=a.g;this.h=a.h;this.j=-1;m[this.g]&&r(this,2);q(this);t(this)}handleClick(){this.i=!0;n.setTimeout(()=>{this.i=!1},5E3)}};const w=l(document.currentScript);if(null==w)throw Error("JSC not found 22");var u;const x={},y=w.attributes;for(let a=y.length-1;0<=a;a--){const b=y[a].name;0===b.indexOf("data-jcp-")&&(x[b.substring(9)]=y[a].value)}u=x;window.window_focus_for_click=new v;}).call(this);
