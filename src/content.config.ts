import { defineCollection } from 'astro:content';
import { glob } from 'astro/loaders';
import { z } from 'astro/zod';

const posts = defineCollection({
  loader: glob({ pattern: '*.md', base: './posts' }),
  schema: z.object({
    title: z.string(),
    date: z.coerce.date().optional(),
    updated: z.coerce.date().optional(),
    draft: z.boolean().default(false),
    tags: z.array(z.string().trim().min(1)).min(1).default(['일반']),
    portfolio: z.boolean().default(false),
    slug: z.string().optional(),
    description: z.string().optional(),
  }),
});

export const collections = { posts };
