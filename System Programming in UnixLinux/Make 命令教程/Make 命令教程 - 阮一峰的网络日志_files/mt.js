// if (window!=top) top.location.href =window.location.href; 

try{
  window.top.location.hostname;
    if (top.location.hostname != window.location.hostname)
    {
     top.location.href =window.location.href;
    }
}
catch(e){
   top.location.href =window.location.href;
}

// Copyright (c) 1996-1997 Athenia Associates.
// http://www.webreference.com/js/
// License is granted if and only if this entire
// copyright notice is included. By Tomer Shiran.

function setCookie (name, value, expires, path, domain, secure) {
    var curCookie = name + "=" + escape(value) + (expires ? "; expires=" + expires : "") +
        (path ? "; path=" + path : "") + (domain ? "; domain=" + domain : "") + (secure ? "secure" : "");
    document.cookie = curCookie;
}

function getCookie (name) {
    var prefix = name + '=';
    var c = document.cookie;
    var nullstring = '';
    var cookieStartIndex = c.indexOf(prefix);
    if (cookieStartIndex == -1)
        return nullstring;
    var cookieEndIndex = c.indexOf(";", cookieStartIndex + prefix.length);
    if (cookieEndIndex == -1)
        cookieEndIndex = c.length;
    return unescape(c.substring(cookieStartIndex + prefix.length, cookieEndIndex));
}

function deleteCookie (name, path, domain) {
    if (getCookie(name))
        document.cookie = name + "=" + ((path) ? "; path=" + path : "") +
            ((domain) ? "; domain=" + domain : "") + "; expires=Thu, 01-Jan-70 00:00:01 GMT";
}

function fixDate (date) {
    var base = new Date(0);
    var skew = base.getTime();
    if (skew > 0)
        date.setTime(date.getTime() - skew);
}

function rememberMe (f) {
    var now = new Date();
    fixDate(now);
    now.setTime(now.getTime() + 365 * 24 * 60 * 60 * 1000);
    now = now.toGMTString();
    if (f.author != undefined)
       setCookie('mtcmtauth', f.author.value, now, '/', '', '');
    if (f.email != undefined)
       setCookie('mtcmtmail', f.email.value, now, '/', '', '');
    if (f.url != undefined)
       setCookie('mtcmthome', f.url.value, now, '/', '', '');
}

function forgetMe (f) {
    deleteCookie('mtcmtmail', '/', '');
    deleteCookie('mtcmthome', '/', '');
    deleteCookie('mtcmtauth', '/', '');
    f.email.value = '';
    f.author.value = '';
    f.url.value = '';
}

function hideDocumentElement(id) {
    var el = document.getElementById(id);
    if (el) el.style.display = 'none';
}

function showDocumentElement(id) {
    var el = document.getElementById(id);
    if (el) el.style.display = 'block';
}

var commenter_name;

function individualArchivesOnLoad(commenter_name) {

    hideDocumentElement('trackbacks-info');



    if (document.comments_form) {
        if (document.comments_form.email != undefined &&
            (mtcmtmail = getCookie("mtcmtmail")))
            document.comments_form.email.value = mtcmtmail;
        if (document.comments_form.author != undefined &&
            (mtcmtauth = getCookie("mtcmtauth")))
            document.comments_form.author.value = mtcmtauth;
        if (document.comments_form.url != undefined &&
            (mtcmthome = getCookie("mtcmthome")))
            document.comments_form.url.value = mtcmthome;
        if (mtcmtauth || mtcmthome) {
            document.comments_form.bakecookie.checked = true;
        } else {
            document.comments_form.bakecookie.checked = false;
        }
    }
}

function writeTypeKeyGreeting(commenter_name, entry_id) {

}

function RemoveBlockquote(strText)
{
 var regEx = /<blockquote>(.|\n|\r)*<\/blockquote>/ig;
 regEx.multiline=true;
 return strText.replace(regEx, "");
}

function RemoveHTML(strText)
{
 var regEx = /<[^>]*>/g;
 return strText.replace(regEx, "");
}

function CommentQuote(v,f) {


window.location.href=window.location.href+"#comment-text";

string=document.forms["comments_form"].text.value;
string2=ignoreSpaces(RemoveHTML(RemoveBlockquote(document.getElementById(v).innerHTML)));
document.forms["comments_form"].text.value="<blockquote>\n<pre>引用"+f+"的发言：</pre>\n"+string2+"\n</blockquote>\n\n"+string;


return true;
}

function ignoreSpaces(string) {
var temp = "";
string = '' + string;
splitstring = string.split("  "); //双引号之间是个空格；
for(i = 0; i < splitstring.length; i++)
temp += splitstring[i];
return temp;
}

var bar = 0;
            var line = "||";
            var amount ="||";

function pleaseWait() {
if(document.getElementById('comment-text').value.length>1200){
alert('留言请勿超过1200字！');
return false;
}

if(!document.forms["comments_form"].author.value){
alert('请填写“您的大名”！');
return false;
}

if(document.forms["comments_form"].email.value.length<7 || document.forms["comments_form"].email.value.indexOf("@")==-1){
alert('请正确填写电子邮件地址！');
return false;
}

if(document.getElementById('comment-text').value.length<2){
alert('留言不得为空！');
return false;
}

document.getElementById("comment-submit").style.visibility="hidden";
document.getElementById("wait").style.display="block";
          stick_count();
if (document.forms["comments_form"].armor)
            document.forms["comments_form"].armor.value = '493b793496197fb44387464d8c8c8cb4091a0b94';
return true;
}


function stick_count(){
            bar= bar+2;
            amount =amount + line;
            document.forms["comments_form"].chart.value=amount;
            document.forms["comments_form"].percent.value=bar+"%";
            if (bar<99)
            {setTimeout("stick_count()",200);}
            else
            {}
}


var MT ={};

document.addEventListener("DOMContentLoaded", function(event) {
   individualArchivesOnLoad(commenter_name);
});

function hab(container) {
  var items = document.querySelectorAll(container + ' a img');
  // console.log(items);
  items = Array.prototype.slice.call(items);
  if (!items.length) return;
  if (!getComputedStyle) return;
  items.forEach(function (i) {
    // console.log(getComputedStyle(i).display);
    if (getComputedStyle(i).display !== 'none') return;
    var src = i.src;
    // console.log(src);
    if (!src) return;
    // src = Array.prototype.slice.call(src);
    // src.splice(src.lastIndexOf('.'), 0, '_backup');
    src = src.split('/');
    // src[src.length - 1] = 'backup_' + src[src.length - 1];
    var imgFileName = src[src.length - 1];
    if (imgFileName.substr(0, 4) === 'sup_') {
       imgFileName = 'cre_' + src[src.length - 1].substr(4); 
       src[src.length - 1] = imgFileName;
    }
    if (src[2] === 'www.ruanyifeng.com') {
      src = src.join('/');
    } else {
      src = '/blog/images/' + src[src.length - 1];
    } 
    var img = new Image();
    img.src = src;
    if (i.width) img.width = i.width;
    img.style = 'border: none;';
    i.parentNode.appendChild(img);
  });
}