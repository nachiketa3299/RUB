document.addEventListener('DOMContentLoaded', function() {
  // 호버 컨테이너 생성
  const hoverContainer = document.createElement('div');
  hoverContainer.className = 'image-hover-container';
  const hoverImage = document.createElement('img');
  hoverContainer.appendChild(hoverImage);
  document.body.appendChild(hoverContainer);
  
  // 호버 상태 추적 변수
  let isHovering = false;
  let hoverTimeout = null;

  // 모든 이미지에 이벤트 리스너 추가
  document.querySelectorAll('figure.rub_img img').forEach(img => {
    img.addEventListener('mouseenter', function(e) {
      // 원본 이미지 URL 가져오기
      const originalSrc = this.src;
      
      // 호버 이미지 설정
      hoverImage.src = originalSrc;
      
      // 호버 상태 설정
      isHovering = true;
      
      // 호버 컨테이너 표시
      hoverContainer.style.display = 'block';
      
      // 마우스 위치에 따라 호버 컨테이너 위치 조정
      updateHoverPosition(e);
    });
    
    img.addEventListener('mousemove', function(e) {
      updateHoverPosition(e);
    });
    
    img.addEventListener('mouseleave', function() {
      isHovering = false;
      
      // 약간의 지연 후 호버 컨테이너 숨김 (깜빡임 방지)
      clearTimeout(hoverTimeout);
      hoverTimeout = setTimeout(() => {
        if (!isHovering) {
          hoverContainer.style.display = 'none';
        }
      }, 100);
    });
    
    // 호버 컨테이너에 이벤트 리스너 추가
    hoverContainer.addEventListener('mouseenter', function() {
      isHovering = true;
    });
    
    hoverContainer.addEventListener('mouseleave', function() {
      isHovering = false;
      
      // 약간의 지연 후 호버 컨테이너 숨김 (깜빡임 방지)
      clearTimeout(hoverTimeout);
      hoverTimeout = setTimeout(() => {
        if (!isHovering) {
          hoverContainer.style.display = 'none';
        }
      }, 100);
    });
    
    // 호버 컨테이너 클릭 이벤트 추가
    hoverContainer.addEventListener('click', function() {
      // 새 탭에서 이미지 열기
      window.open(hoverImage.src, '_blank');
    });
    
    // 호버 컨테이너에 커서 스타일 추가
    hoverContainer.style.cursor = 'pointer';
  });
  
  // 호버 컨테이너 위치 업데이트 함수
  function updateHoverPosition(e) {
    const offset = 20; // 마우스와의 간격
    
    // 화면 경계 확인
    const containerWidth = hoverContainer.offsetWidth;
    const containerHeight = hoverContainer.offsetHeight;
    const windowWidth = window.innerWidth;
    const windowHeight = window.innerHeight;
    
    // 항상 마우스 오른쪽에 표시
    let left = e.clientX + offset;
    let top = e.clientY;
    
    // 오른쪽 경계 체크 - 화면을 벗어나면 스크롤 가능하도록
    if (left + containerWidth > windowWidth) {
      left = windowWidth - containerWidth - offset;
    }
    
    // 아래쪽 경계 체크
    if (top + containerHeight > windowHeight) {
      top = windowHeight - containerHeight - offset;
    }
    
    // 위치 적용
    hoverContainer.style.left = left + 'px';
    hoverContainer.style.top = top + 'px';
  }
}); 