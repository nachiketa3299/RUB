# RUB

Astro로 만드는 작은 Markdown 블로그. 태그별 글 목록과 포트폴리오가 있습니다.

Node.js 24 LTS 권장.

```sh
npm ci
npm run dev
npm run build
```

개발 주소: `http://localhost:4321/RUB/`

`posts/글-이름.md`를 만들면 목록에 나타납니다.

```md
---
title: 글 제목
date: 2026-09-05
tags: [일반, 코딩테스트]
---

여기에 글을 씁니다.
```

- `draft: true`인 글은 배포하지 않습니다. `updated`는 수정일입니다.
- `tags`를 생략하면 `일반`입니다. 여러 태그를 붙이면 각 목록에 함께 나오며, 홈에는 일반 → 코딩테스트 → 나머지 태그 순서로 표시됩니다.
- `portfolio: true`인 글은 홈·RSS에서 제외하고 `/portfolio/`의 소개글 상단에 모읍니다. 소개글 자체는 목록에 중복 표시하지 않습니다.
- 기존 글의 `slug`는 예전 주소를 유지합니다. 새 글에서는 생략할 수 있습니다.
- 첨부파일은 `public/media/`에 두고 `![설명](/media/이미지.png)`로 연결합니다.
- 일반 Markdown, HTML, `$수식$`, `$$수식$$`, `plantuml` 코드 블록을 지원합니다. PlantUML은 HTTPS 렌더링 서버를 사용합니다.
- 화면과 CSS는 `src/layouts/Page.astro`에 있습니다. 외부 웹폰트와 사이트 JavaScript는 없습니다.
- `master`에 push하면 GitHub Actions가 빌드해서 GitHub Pages에 배포합니다. 배포 주소는 `astro.config.mjs`에서 설정합니다.
