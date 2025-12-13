let isScrollEnabled = false;

const logs = document.getElementById('logs');

async function updateLogs() {
    await axios({
        method: 'get',
        url: '/api/getLogs',
        timeout: 5000,
        responseType: 'text',
        responseEncoding: 'utf-8'
    })
        .then(response => {
            const data = response.data;
            if (data !== '') {
                logs.innerHTML = data;
                if (isScrollEnabled) {
                    const scrollBox = logs.parentElement;
                    scrollBox.scrollTop = scrollBox.scrollHeight;
                }
            }
        })
        .catch(error => {
            logs.innerHTML = '无法获取日志，Web 服务器可能已关闭\n';
            console.error(error);
        });
}

document.addEventListener('DOMContentLoaded', () => {
    setInterval(updateLogs, 1000);
});

const switchBorder = document.getElementById('switch-border');
const switchBtn = document.getElementById('switch-circle');

switchBorder.addEventListener('click', () => {
    switchBorder.classList.toggle('switchon');
    switchBtn.classList.toggle('switchon');
    isScrollEnabled = !isScrollEnabled;
});