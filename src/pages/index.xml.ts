import { getCollection } from 'astro:content';
import type { APIRoute } from 'astro';

export const GET: APIRoute = async ({ site }) => {
  const escape = (text: string) => text.replace(/[<>&"']/g, (c) => `&#${c.charCodeAt(0)};`);
  const home = new URL(import.meta.env.BASE_URL, site).href;
  const posts = (await getCollection('posts', ({ data }) => !data.draft))
    .sort((a, b) => (b.data.date?.getTime() ?? 0) - (a.data.date?.getTime() ?? 0));
  const items = posts.map(({ id, data }) => {
    const link = escape(`${home}${data.slug ?? id}/`);
    return `<item><title>${escape(data.title)}</title><link>${link}</link><guid>${link}</guid>${data.date ? `<pubDate>${data.date.toUTCString()}</pubDate>` : ''}</item>`;
  }).join('');
  return new Response(`<?xml version="1.0" encoding="UTF-8"?><rss version="2.0"><channel><title>Even Idiots Can Make Game</title><link>${escape(home)}</link><description>게임 개발과 이런저런 것들</description>${items}</channel></rss>`, {
    headers: { 'Content-Type': 'application/rss+xml; charset=utf-8' },
  });
};
