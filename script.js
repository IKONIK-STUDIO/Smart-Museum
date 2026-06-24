// Initialization
document.addEventListener('DOMContentLoaded', function() {
    initializeTheme();
    initializeGallery();
    initializeNews();
});

// Initialize theme
function initializeTheme() {
    const themeSelect = document.getElementById('theme-select');
    const savedTheme = localStorage.getItem('theme') || 'dark';
    
    document.documentElement.setAttribute('data-theme', savedTheme);
    themeSelect.value = savedTheme;
    
    themeSelect.addEventListener('change', function() {
        const selectedTheme = this.value;
        document.documentElement.setAttribute('data-theme', selectedTheme);
        localStorage.setItem('theme', selectedTheme);
    });
}

function initializeGallery() {
    const galleryGrid = document.getElementById('gallery-grid');
    if (!galleryGrid) {
        return;
    }

    const galleryItems = [
        { file: '20260312_151024-1.jpg', label: 'Alex working', summary: 'Alex working on the windows.' },
        { file: '20260313_142958-1.jpg', label: 'Early museum', summary: 'An early look at the museum.' },
        { file: '20260313_143005-1.jpg', label: 'Early museum', summary: 'An early look at the museum.' },
        { file: '20260313_143035-1.jpg', label: 'Early museum', summary: 'An early look at the museum.' },
        { file: '20260327_122636-1.jpg', label: 'Bence working', summary: 'Bence working on the water tanks.' },
        { file: '20260327_134925-1.jpg', label: 'Roof work', summary: 'Bence working on the roof.' },
        { file: '20260327_135507-1.jpg', label: 'Roof work', summary: 'Bence painting the roof.' },
        { file: '20260327_135533-1.jpg', label: 'Roof work', summary: 'Bence painting the roof from a weird angle.' },
        { file: '20260330_140740-1.jpg', label: 'A team working', summary: 'Everyone working together on the project.' },
        { file: '20260402_014438-1.jpg', label: 'Coding', summary: 'Áron coding the software.' },
        { file: '20260416_141424-1.jpg', label: 'Voltage meter assembly', summary: 'Bence and Alex assembling the voltage meter.' },
        { file: '20260417_091627-1.jpg', label: 'Grass mowing', summary: 'Bence and Alex preparing the grass.' },
        { file: '20260420_141338-1.jpg', label: 'Team work', summary: 'Team work makes the dream work.' },
        { file: '20260423_150822-1.jpg', label: 'Team work', summary: 'Team work makes the dream work.' },
        { file: '20260427_150943-1.jpg', label: 'Team work', summary: 'Team work makes the dream work.' },
        { file: '20260513_144945-1.jpg', label: 'Early electronics', summary: 'An early look at the electronic components.' },
        { file: '20260513_145702-1.jpg', label: 'Light sensor', summary: 'A close-up of the light sensor component.' },
        { file: '20260513_145939-1.jpg', label: 'Team work', summary: 'Team work makes the dream work.' },
        { file: '20260513_150651-1.jpg', label: 'Alex soldering.', summary: 'It is just a simple soldering job.' },
        { file: '20260516_110631-1.jpg', label: 'Alex at a museum', summary: 'Alex went on to visit a museum.' },
        { file: '20260527_093052-1.jpg', label: 'An almost finished museum', summary: 'Make sure to finish the museum.' },
        { file: '20260527_093542-1.jpg', label: 'An almost finished museum', summary: 'Make sure to finish the museum.' },
        { file: '20260527_143326-1.jpg', label: 'Lasers', summary: 'A close-up of the laser security system.' },
        { file: '20260608_142047-1.jpg', label: 'Production day', summary: 'It is time to film the video.' },
        { file: '20260608_142203-1.jpg', label: 'Just a museum', summary: 'A smart museum.' },
        { file: '20260609_145733-1.jpg', label: 'Selfie', summary: 'Alex took a selfie :)' },
        { file: '20260615_194613-1.jpg', label: 'The pain of tracking', summary: 'It is hard to track an object in Davinci Resolve.' },
        { file: '20260616_141134-1.jpg', label: 'Cable managment', summary: 'Look how beautiful the cable management is.' },
        { file: '20260616_141145-1.jpg', label: 'Smart window machine', summary: 'Look how clean it is.' },
        { file: 'alex-egyeni.jpg', label: 'Strong man', summary: 'Alex is really strong.' },
        { file: 'alex-1.jpg', label: 'Just Alex', summary: 'Alex being Alex.' },
        { file: 'aramersossegmero-1.jpg', label: 'Voltage sensor', summary: 'A close-up of the voltage sensor component.' },
        { file: 'bence-egyeni.jpg', label: 'Bence the electrician', summary: 'Bence can solder too.' },
        { file: 'boss-egyeni.jpg', label: 'Coach photo', summary: 'Coach photo.' },
        { file: 'csapat-3-1.jpg', label: 'Team photo', summary: 'Team photo.' },
        { file: 'csapat-4-1.jpg', label: 'Team photo', summary: 'The official team photo.' },
        { file: 'hangszoro-1.jpg', label: 'Speaker module', summary: 'It sounds really goood.' },
        { file: 'homerseklet-teszt.jpg', label: 'Temperature test', summary: 'Testing the temperature control logic in practice.' },
        { file: 'image-1.png', label: 'Painting', summary: 'Paint smells awful.' },
        { file: 'lcd-1.jpg', label: 'LCD display', summary: 'The display that shows system information.' },
        { file: 'muzeum.jpg', label: 'Museum model', summary: 'Main model of the intelligent museum project.' },
        { file: 'napelem-teszt-1.jpg', label: 'Solar tracking test', summary: 'Test of the solar tracking and light-following system.' },
        { file: 'riaszto-1.jpg', label: 'Alarm system', summary: 'Alarm hardware used for security warnings.' },
        { file: 'riaszto-teszt.jpg', label: 'Alarm test', summary: 'Testing the alarm behavior during development.' },
        { file: 'roadmap-1.jpg', label: 'Planning', summary: 'An early photo of us planning the project.' },
        { file: 'roadmap-2.jpg', label: 'Building', summary: 'An early photo of us building the project.' },
        { file: 'roadmap-3.jpg', label: 'Electronics', summary: 'An early photo of us working on the electronics.' },
        { file: 'roadmap-4.jpg', label: 'Coding', summary: 'An early photo of us coding the project.' },
        { file: 'roadmap-5.jpg', label: 'Planning the solar panel integration', summary: 'Planning the integration of solar panels into the system.' },
        { file: 'roadmap-6.jpg', label: 'Almost done', summary: 'A pretty recent picture.' },
        { file: 'tuz-teszt.jpg', label: 'Fire test', summary: 'Fire detection test and related warning behavior.' },
        { file: 'wc-1.jpg', label: 'WC subsystem', summary: 'Subsystem handling the WC water logic.' },
        { file: 'wro-polo-dizajn-eleje.png', label: 'WRO shirt front design', summary: 'Front design of the team WRO shirt.' },
        { file: 'wro-polo-dizajn-hatulja.png', label: 'WRO shirt back design', summary: 'Back design of the team WRO shirt.' },
        { file: 'aron-egyeni.jpg', label: 'Áron coding', summary: 'Just Áron doing his thing.' }
    ];

    // gallery will use the shared viewer; ensure it's initialized
    if (typeof window.initializeViewer === 'function') {
        window.initializeViewer();
    }

    const getThumbPath = function(fileName) {
        const extensionIndex = fileName.lastIndexOf('.');
        const thumbName = (extensionIndex === -1 ? fileName : fileName.slice(0, extensionIndex)) + '.jpg';

        return encodeURI('images/thumbs/' + thumbName);
    };

    galleryGrid.innerHTML = galleryItems.map(function(item) {
        const imagePath = encodeURI('images/' + item.file);
        const thumbPath = getThumbPath(item.file);
        const altText = item.label;

        return `
            <button type="button" class="gallery-item" data-image="${imagePath}" data-label="${item.label}" data-file="${item.file}">
                <img src="${thumbPath}" alt="${altText}" loading="lazy" decoding="async">
            </button>
        `;
    }).join('');

    // attach gallery buttons to open viewer using the shared function
    galleryGrid.addEventListener('click', function(event) {
        const item = event.target.closest('.gallery-item');
        if (!item) return;
        if (typeof window.openViewerWithList === 'function') {
            // open with the full galleryItems list from this file set
            const files = galleryItems.map(function(it){ return { file: it.file, label: it.label, summary: it.summary }; });
            window.openViewerWithList(files, galleryItems.findIndex(it => it.file === item.dataset.file));
        }
    });
}

// --- Shared photo viewer ---
(function(){
    let viewer, viewerMedia, viewerImage, viewerTitle, viewerSummary, viewerPrev, viewerNext, viewerZoom;
    let viewerItems = [];
    let currentIndex = 0;
    let zoomLevelIndex = 0;
    const zoomLevels = [100,150,200];

    function updateZoomState() {
        const zoomPercent = zoomLevels[zoomLevelIndex] || 100;
        if (!viewer) return;
        if (zoomPercent > 100) {
            viewer.classList.add('zoomed');
            viewerZoom.setAttribute('aria-label', 'Zoom level ' + zoomPercent + ' percent. Click to change zoom.');
            viewerImage.style.width = 'auto';
            viewerImage.style.minWidth = zoomPercent + '%';
            viewerImage.style.maxWidth = 'none';
            viewerImage.style.maxHeight = 'none';
        } else {
            viewer.classList.remove('zoomed');
            viewerZoom.setAttribute('aria-label', 'Zoom level 100 percent. Click to zoom in.');
            viewerImage.style.width = 'auto';
            viewerImage.style.minWidth = '0';
            viewerImage.style.maxWidth = '100%';
            viewerImage.style.maxHeight = '72vh';
        }
        viewerZoom.textContent = '🔍';
    }

    function resetZoom() {
        zoomLevelIndex = 0;
        updateZoomState();
        if (viewerMedia) { viewerMedia.scrollTop = 0; viewerMedia.scrollLeft = 0; }
    }

    function renderCurrentItem() {
        const currentItem = viewerItems[currentIndex];
        if (!currentItem) return;
        viewerImage.src = encodeURI('images/' + currentItem.file);
        viewerImage.alt = currentItem.label || '';
        viewerTitle.textContent = currentItem.label || '';
        viewerSummary.textContent = currentItem.summary || '';
    }

    function showPrevious() {
        currentIndex = (currentIndex - 1 + viewerItems.length) % viewerItems.length;
        resetZoom();
        renderCurrentItem();
    }

    function showNext() {
        currentIndex = (currentIndex + 1) % viewerItems.length;
        resetZoom();
        renderCurrentItem();
    }

    function closeViewer() {
        if (!viewer) return;
        viewer.classList.remove('active');
        viewer.setAttribute('aria-hidden', 'true');
        document.body.classList.remove('viewer-open');
    }

    window.initializeViewer = function() {
        if (viewer) return; // already initialized
        viewer = document.getElementById('photo-viewer');
        if (!viewer) return;
        viewerMedia = document.getElementById('photo-viewer-media');
        viewerImage = document.getElementById('photo-viewer-image');
        viewerTitle = document.getElementById('photo-viewer-title');
        viewerSummary = document.getElementById('photo-viewer-summary');
        viewerPrev = document.getElementById('photo-viewer-prev');
        viewerNext = document.getElementById('photo-viewer-next');
        viewerZoom = document.getElementById('photo-viewer-zoom');

        if (!viewer || !viewerImage) return;

        viewerPrev && viewerPrev.addEventListener('click', function(e){ e.stopPropagation(); showPrevious(); });
        viewerNext && viewerNext.addEventListener('click', function(e){ e.stopPropagation(); showNext(); });
        viewerZoom && viewerZoom.addEventListener('click', function(e){ e.stopPropagation(); zoomLevelIndex = (zoomLevelIndex + 1) % zoomLevels.length; updateZoomState(); });
        viewer.addEventListener('click', function(e){ if (e.target.hasAttribute('data-viewer-close')) closeViewer(); });
        viewer.querySelector('.photo-viewer-panel')?.addEventListener('wheel', function(event){
            if (!viewer.classList.contains('active')) return;
            if (zoomLevelIndex > 0) { viewerMedia.scrollTop += event.deltaY; viewerMedia.scrollLeft += event.deltaX; event.preventDefault(); return; }
            event.preventDefault(); this.scrollTop += event.deltaY;
        }, { passive: false });
        document.addEventListener('keydown', function(event){ if (!viewer || !viewer.classList.contains('active')) return; if (event.key === 'Escape') closeViewer(); else if (event.key === 'ArrowLeft') { event.preventDefault(); showPrevious(); } else if (event.key === 'ArrowRight') { event.preventDefault(); showNext(); } else if (event.key === '+' || event.key === '=') { event.preventDefault(); zoomLevelIndex = Math.min(zoomLevelIndex + 1, zoomLevels.length - 1); updateZoomState(); } else if (event.key === '-') { event.preventDefault(); zoomLevelIndex = Math.max(zoomLevelIndex - 1, 0); updateZoomState(); } });
    };

    // files: array of {file,label,summary} or array of filenames
    window.openViewerWithList = function(files, startIndex, options) {
        options = options || {};
        window.initializeViewer();
        if (!viewer) return;
        viewerItems = files.map(function(f){ if (typeof f === 'string') return { file: f }; return f; });
        currentIndex = Math.max(0, Math.min(startIndex || 0, viewerItems.length-1));

        // apply UI options
        if (options.controls === false) {
            viewer.classList.add('hide-controls');
        } else {
            viewer.classList.remove('hide-controls');
        }

        if (options.overlayText) {
            viewer.classList.add('overlay-meta');
        } else {
            viewer.classList.remove('overlay-meta');
        }

        resetZoom();
        renderCurrentItem();
        viewer.classList.add('active');
        viewer.setAttribute('aria-hidden','false');
        document.body.classList.add('viewer-open');
    };
})();

function initializeNews() {
    const newsSection = document.querySelector('.news-section');
    const newsHeader = document.querySelector('.news-header');
    const featuredPost = document.querySelector('.featured-post');
    const modal = document.getElementById('news-modal');
    const modalPanel = modal ? modal.querySelector('.news-modal-panel') : null;
    const modalBackdrop = modal ? modal.querySelector('.news-modal-backdrop') : null;
    const modalContent = document.getElementById('news-modal-content');
    const zoomablePosts = Array.from(document.querySelectorAll('.featured-post, .timeline-card'));

    if (!newsSection || !featuredPost || !modal || !modalPanel || !modalBackdrop || !modalContent || zoomablePosts.length === 0) {
        return;
    }

    const closeModal = function() {
        modal.classList.remove('active');
        modal.setAttribute('aria-hidden', 'true');
        document.body.classList.remove('news-modal-open');
        document.body.style.overflow = '';
        modal.removeAttribute('style');
        modalPanel.removeAttribute('style');
        modalBackdrop.removeAttribute('style');
        modalContent.innerHTML = '';
    };

    // remove interactive role/handlers so clicking does nothing
    zoomablePosts.forEach(function(post) {
        post.removeAttribute('tabindex');
        post.removeAttribute('role');
        post.removeAttribute('aria-haspopup');
    });

    if (newsHeader) {
        newsHeader.tabIndex = 0;
        newsHeader.setAttribute('role', 'button');
        newsHeader.setAttribute('aria-haspopup', 'dialog');
    }

    const openModalWithPost = function(post) {
        if (!post) {
            return;
        }

        Object.assign(modal.style, {
            position: 'fixed',
            inset: '0',
            display: 'flex',
            alignItems: 'center',
            justifyContent: 'center',
            zIndex: '1400',
            padding: '24px'
        });

        Object.assign(modalBackdrop.style, {
            position: 'absolute',
            inset: '0',
            background: 'rgba(2, 6, 23, 0.55)',
            backdropFilter: 'blur(10px)'
        });

        Object.assign(modalPanel.style, {
            position: 'relative',
            zIndex: '1',
            width: 'min(100%, 980px)',
            maxHeight: '90vh',
            overflow: 'auto',
            borderRadius: '18px',
            border: '1px solid var(--container-border)',
            background: 'var(--container-bg)',
            boxShadow: '0 26px 80px rgba(0, 0, 0, 0.38)',
            padding: '22px'
        });

        modalContent.innerHTML = '';

        const clonedPost = post.cloneNode(true);
        clonedPost.classList.add('news-modal-post');
        clonedPost.removeAttribute('role');
        clonedPost.removeAttribute('tabindex');
        clonedPost.removeAttribute('aria-pressed');
        clonedPost.removeAttribute('aria-haspopup');

        modalContent.appendChild(clonedPost);

        modal.classList.add('active');
        modal.setAttribute('aria-hidden', 'false');
        document.body.classList.add('news-modal-open');
        document.body.style.overflow = 'hidden';
    };

    const openFeaturedPost = function() {
        openModalWithPost(featuredPost);
    };

    // disable header interaction
    if (newsHeader) {
        newsHeader.removeAttribute('tabindex');
        newsHeader.removeAttribute('role');
        newsHeader.removeAttribute('aria-haspopup');
    }

    // Helper to construct thumbnail path used in gallery
    const buildThumbPath = function(fileName) {
        const extensionIndex = fileName.lastIndexOf('.');
        const base = (extensionIndex === -1 ? fileName : fileName.slice(0, extensionIndex));
        return encodeURI('images/thumbs/' + base + '.jpg');
    };

    // Mapping from data-key -> array of image filenames to show inline
    const imageMap = {
        'february-22': ['roadmap-1.jpg'],
        'march-1': ['20260417_091627-1.jpg'],
        'march-8': ['roadmap-3.jpg'],
        'march-15': ['20260402_014438-1.jpg'],
        'march-29': ['20260313_143005-1.jpg'],
        'april-5': ['20260513_144945-1.jpg'],
        'april-18': ['napelem-teszt-1.jpg'],
        'may-3': ['tuz-teszt.jpg'],
        'may-17': ['homerseklet-teszt.jpg'],
        'june-1': ['20260427_150943-1.jpg'],
        'june-15': ['20260608_142047-1.jpg'],
        'june-22': ['csapat-4-1.jpg']
    };

    const toggleInlineImages = function(post, key) {
        if (!key) return false;
        const existing = post.querySelector('.news-inline-images');
        if (existing) {
            existing.remove();
            return true;
        }
        const files = imageMap[key];
        if (!files || files.length === 0) return false;
        const container = document.createElement('div');
        container.className = 'news-inline-images';
        files.forEach(function(f) {
            const a = document.createElement('a');
            a.href = 'images/' + f;
            a.target = '_blank';
            a.rel = 'noopener noreferrer';
            const img = document.createElement('img');
            img.src = buildThumbPath(f);
            img.alt = f;
            a.appendChild(img);
            container.appendChild(a);
        });
        post.appendChild(container);
        return true;
    };

    // disable click handlers on news items — do nothing on click
    // (previously opened photo viewer or modal; removed per user request)
    newsSection.addEventListener('click', function(event) {
        // intentionally no-op
    });

    // disable keyboard interaction on news items
    newsSection.addEventListener('keydown', function(event) {
        // intentionally no-op
    });

    modal.addEventListener('click', function(event) {
        if (event.target.hasAttribute('data-news-modal-close')) {
            closeModal();
        }
    });

    document.addEventListener('keydown', function(event) {
        if (!modal.classList.contains('active')) {
            return;
        }

        if (event.key === 'Escape') {
            closeModal();
        }
    });
}