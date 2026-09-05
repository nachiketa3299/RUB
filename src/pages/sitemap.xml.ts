import { getCollection } from 'astro:content';
import type { APIRoute } from 'astro';

export const GET: APIRoute = async ({ site }) => {
  const home = new URL(import.meta.env.BASE_URL, site).href;
  const posts = await getCollection('posts', ({ data }) => !data.draft);
  const urls = [home, ...posts.map(({ id, data }) => `${home}${data.slug ?? id}/`)];
  return new Response(`<?xml version="1.0" encoding="UTF-8"?><urlset xmlns="http://www.sitemaps.org/schemas/sitemap/0.9">${urls.map((url) => `<url><loc>${url.replaceAll('&', '&amp;')}</loc></url>`).join('')}</urlset>`, {
    headers: { 'Content-Type': 'application/xml; charset=utf-8' },
  });
};
