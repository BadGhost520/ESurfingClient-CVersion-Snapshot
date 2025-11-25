// 内容元素
const homepageContent = document.getElementById('homepage-content');
const logContent = document.getElementById('log-content');
const settingsContent = document.getElementById('settings-content');
const aboutContent = document.getElementById('about-content');
// 侧边栏元素
const sidebarLogo = document.getElementById('sidebar-logo');
const homepage = document.getElementById('homepage');
const log = document.getElementById('log');
const settings = document.getElementById('settings');
const about = document.getElementById('about');

function toggleHomepage() {
    logContent.classList.remove('active');
    settingsContent.classList.remove('active');
    aboutContent.classList.remove('active');
    log.classList.remove('on');
    settings.classList.remove('on');
    about.classList.remove('on');
    if (!homepageContent.classList.contains('active')) homepageContent.classList.add('active');
    if (!homepage.classList.contains('on')) homepage.classList.add('on');
}

function toggleLog() {
    homepageContent.classList.remove('active');
    settingsContent.classList.remove('active');
    aboutContent.classList.remove('active');
    homepage.classList.remove('on');
    settings.classList.remove('on');
    about.classList.remove('on');
    if (!logContent.classList.contains('active')) logContent.classList.add('active');
    if (!log.classList.contains('on')) log.classList.add('on');
}

function toggleSettings() {
    homepageContent.classList.remove('active');
    logContent.classList.remove('active');
    aboutContent.classList.remove('active');
    homepage.classList.remove('on');
    log.classList.remove('on');
    about.classList.remove('on');
    if (!settingsContent.classList.contains('active')) settingsContent.classList.add('active');
    if (!settings.classList.contains('on')) settings.classList.add('on');
}

function toggleAbout() {
    homepageContent.classList.remove('active');
    logContent.classList.remove('active');
    settingsContent.classList.remove('active');
    homepage.classList.remove('on');
    log.classList.remove('on');
    settings.classList.remove('on');
    if (!aboutContent.classList.contains('active')) aboutContent.classList.add('active');
    if (!about.classList.contains('on')) about.classList.add('on');
}

sidebarLogo.addEventListener('click', () => {
    toggleHomepage();
});

homepage.addEventListener('click', () => {
    toggleHomepage();
});

log.addEventListener('click', () => {
    toggleLog();
});

settings.addEventListener('click', () => {
    toggleSettings();
});

about.addEventListener('click', () => {
    toggleAbout();
});