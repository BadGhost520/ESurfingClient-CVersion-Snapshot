const logs = document.getElementById('logs');

async function updateLogs() {
    try {
        const response = await fetch('/api/getLogs', {
            cache: 'no-store',
            signal: AbortSignal.timeout(3000)
        });
        const data = await response.text();

        if (data !== 'nonew') {
            if (logs.innerHTML !== data) {
                logs.innerHTML = data;
                const scrollBox = logs.parentElement;
                scrollBox.scrollTop = scrollBox.scrollHeight;
            }
        } else {
            console.log('No new logs');
        }
    } catch (error) {
        console.error('获取日志失败:', error);
    }
}

// 使用 DOMContentLoaded 而不是 load
document.addEventListener('DOMContentLoaded', () => {
    setInterval(updateLogs, 5000);
});