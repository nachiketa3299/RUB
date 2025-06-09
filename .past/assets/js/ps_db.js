document.addEventListener('DOMContentLoaded', function() {
  const table = document.getElementById('psTable');
  const headers = table.querySelectorAll('th');
  let currentSort = { column: null, direction: 'asc' };

  // 날짜 표시 형식 변환 함수
  function formatDays(days) {
    if (days === -1) return '-';
    if (days === 0) return '오늘';
    return `${days}일전`;
  }

  // 초기 정렬 함수
  function sortTable(column, direction) {
    const header = Array.from(headers).find(h => h.dataset.sort === column);
    if (!header) return;

    // Remove previous sort indicators
    headers.forEach(h => h.classList.remove('asc', 'desc'));
    
    // Add new sort indicator
    header.classList.add(direction);
    
    // Sort the table
    const tbody = table.querySelector('tbody');
    const rows = Array.from(tbody.querySelectorAll('tr'));
    
    rows.sort((a, b) => {
      let aValue = a.querySelector(`td:nth-child(${Array.from(header.parentElement.children).indexOf(header) + 1})`).textContent;
      let bValue = b.querySelector(`td:nth-child(${Array.from(header.parentElement.children).indexOf(header) + 1})`).textContent;
      
      // Special handling for rank sorting
      if (column === 'rank') {
        aValue = a.querySelector('.rank').dataset.rank;
        bValue = b.querySelector('.rank').dataset.rank;
      }
      
      // Special handling for solved date sorting
      if (column === 'solved') {
        aValue = parseInt(a.querySelector('.solved-date').dataset.days);
        bValue = parseInt(b.querySelector('.solved-date').dataset.days);
      }
      
      // 숫자 비교
      if (!isNaN(aValue) && !isNaN(bValue)) {
        if (direction === 'asc') {
          return aValue - bValue;
        } else {
          return bValue - aValue;
        }
      }
      
      // 문자열 비교
      if (direction === 'asc') {
        return aValue.localeCompare(bValue);
      } else {
        return bValue.localeCompare(aValue);
      }
    });
    
    // Reorder the rows and update date display
    rows.forEach(row => {
      tbody.appendChild(row);
      const daysCell = row.querySelector('.solved-date');
      if (daysCell) {
        const days = parseInt(daysCell.dataset.days);
        daysCell.textContent = formatDays(days);
      }
    });
    
    currentSort = { column, direction };
  }

  // 초기 정렬 실행 (풀이일 기준 오름차순)
  sortTable('solved', 'asc');

  // 헤더 클릭 이벤트
  headers.forEach(header => {
    header.addEventListener('click', () => {
      const column = header.dataset.sort;
      const direction = currentSort.column === column && currentSort.direction === 'asc' ? 'desc' : 'asc';
      sortTable(column, direction);
    });
  });
}); 