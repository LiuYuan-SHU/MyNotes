function checker() {
  var img = document.querySelector('img[src^="http://www.ruanyifeng.com/blog/images"]');
  if (img && window.getComputedStyle(img).display === 'none'){
    var sponsor = document.querySelector('.entry-sponsor');
    var prompt = document.createElement('div');
    prompt.style = 'border: 1px solid #c6c6c6;border-radius: 4px;background-color: #f5f2f0;padding: 15px; font-size: 16px;';
    prompt.innerHTML = '<p>您使用了广告拦截器，导致本站内容无法显示。</p><p>请将 www.ruanyifeng.com 加入白名单，解除广告屏蔽后，刷新页面，谢谢。</p>';
    sponsor.parentNode.replaceChild(prompt, sponsor);
    document.querySelector('#main-content').innerHTML = '';
  }
}

setTimeout(checker, 1000);

