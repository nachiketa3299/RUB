import { defineConfig } from 'astro/config';
import { unified } from '@astrojs/markdown-remark';
import remarkMath from 'remark-math';
import rehypeKatex from 'rehype-katex';
import { markdown } from './src/markdown.mjs';

const base = '/RUB';

export default defineConfig({
  site: 'https://nachiketa3299.github.io',
  base,
  trailingSlash: 'always',
  markdown: {
    shikiConfig: { theme: 'github-light' },
    processor: unified({
      remarkPlugins: [remarkMath, [markdown, { base }]],
      rehypePlugins: [[rehypeKatex, { output: 'mathml' }]],
    }),
  },
});
