// 内容元素
const dashboardContent = document.getElementById('dashboard-content');
const logContent = document.getElementById('log-content');
const settingsContent = document.getElementById('settings-content');
const aboutContent = document.getElementById('about-content');
// 侧边栏元素
const shortSwitch = document.getElementById('short-switch');
const sidebarLogo = document.getElementById('sidebar-logo');
const sidebarNavs = document.getElementById('sidebar-navs');
const dashboard = document.getElementById('dashboard');
const log = document.getElementById('log');
const settings = document.getElementById('settings');
const about = document.getElementById('about');
// 标题
const docTitle = document.getElementById('title');
// 风格切换
const main = document.getElementById('main');
const allMain = main.querySelectorAll('*');
const sidebar = document.getElementById('sidebar');
const allSidebar = sidebar.querySelectorAll('*');
const sidebarArray = [sidebar, ...allSidebar];

function toggleDashboard() {
    docTitle.innerHTML = '仪表板';
    dashboardContent.classList.add('active');
    dashboard.classList.add('on');
}

function toggleLog() {
    docTitle.innerHTML = '日志';
    logContent.classList.add('active');
    log.classList.add('on');
}

function toggleSettings() {
    docTitle.innerHTML = '设置';
    settingsContent.classList.add('active');
    settings.classList.add('on');
}

function toggleAbout() {
    docTitle.innerHTML = '关于';
    aboutContent.classList.add('active');
    about.classList.add('on');
}

function clearActive() {
    const active = document.querySelectorAll('.active');
    const on = document.querySelectorAll('.on');
    const all = [...active, ...on];
    all.forEach(item => {
        item.classList.remove('active');
        item.classList.remove('on');
    });
}

shortSwitch.addEventListener('click', () => {
    sidebarNavs.classList.toggle('active');
});

document.addEventListener('click', e => {
    if (!shortSwitch.contains(e.target)) {
        sidebarNavs.classList.remove('active');
    }
});

sidebarLogo.addEventListener('click', () => {
    clearActive();
    toggleDashboard();
});

dashboard.addEventListener('click', () => {
    clearActive();
    toggleDashboard();
});

log.addEventListener('click', () => {
    clearActive();
    toggleLog();
});

settings.addEventListener('click', () => {
    clearActive();
    toggleSettings();
    getSettings();
});

about.addEventListener('click', () => { 
    clearActive();
    toggleAbout();
});

async function switchDocumentStyle() {
    const width = document.documentElement.clientWidth;
    if (width < 768) {
        allMain.forEach(item => {
            if (!item.classList.contains('short')) item.classList.add('short')
        })
    } else {
        sidebarNavs.classList.remove('active');
        allMain.forEach(item => {
            item.classList.remove('short')
        })
    }
}

async function initSwitchDocumentWidth() {
    await switchDocumentStyle();
    window.addEventListener('resize', switchDocumentStyle);
}

window.addEventListener('load', () => {
    initSwitchDocumentWidth();
    clearActive();
    toggleDashboard();
});