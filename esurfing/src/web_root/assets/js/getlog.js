let isUpdating = false;
let lastContentHash = null;
function simpleHash(str) {
    let hash = 0;
    for (let i = 0; i < str.length; i++) {
        const char = str.charCodeAt(i);
        hash = ((hash << 5) - hash) + char;
        hash = hash & hash;
    }
    return hash;
}

async function readLogFile() {
    try {
        const response = await fetch('/logs/run.log');
        if (!response.ok) {
            throw new Error(`HTTP error! status: ${response.status}`);
        }
        return await response.text();
    } catch (error) {
        console.error('读取文件失败:', error);
        return '无日志输出或 Web 服务器已关闭';
    }
}

async function updateLogs() {
    if (isUpdating) return;
    
    isUpdating = true;
    
    try {
        const logsElement = document.querySelector('.logs');
        if (logsElement) {
            const logContent = await readLogFile();
            const currentHash = simpleHash(logContent);
            
            if (currentHash !== lastContentHash) {
                lastContentHash = currentHash;
                logsElement.textContent = logContent;

                const scrollBox = logsElement.parentElement;
                scrollBox.scrollTop = scrollBox.scrollHeight;

                console.log('日志已更新');
            }
        }
    } catch (error) {
        console.error('更新日志失败:', error);
    } finally {
        isUpdating = false;
    }
}

document.addEventListener('DOMContentLoaded', function() {
    updateLogs();
    setInterval(updateLogs, 500);
});