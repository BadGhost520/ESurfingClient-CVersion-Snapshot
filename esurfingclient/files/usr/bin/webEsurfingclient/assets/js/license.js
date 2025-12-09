fetch('assets/license/LICENSE.txt')
    .then(response => {
        if (!response.ok) {
            throw new Error('Network response was not ok');
        }
        return response.text();
    })
    .then(text => {
        document.getElementById('license').textContent = text;
    })
    .catch(error => {
        console.error('Error loading file:', error);
        document.getElementById('license').textContent = '无法加载声明文件';
    });