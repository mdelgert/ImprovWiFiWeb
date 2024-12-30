import { defineConfig } from 'vite';
import { viteStaticCopy } from 'vite-plugin-static-copy';

export default defineConfig(({ mode }) => {
  const isGitHubPages = process.env.GITHUB_REPOSITORY;
  const basePath = isGitHubPages ? `/${process.env.GITHUB_REPOSITORY.split('/')[1]}/` : '/';

  return {
    root: 'public',
    build: {
      outDir: '../dist',
      emptyOutDir: true,
    },
    base: basePath,
    plugins: [
      viteStaticCopy({
        targets: [
          {
            src: 'firmware/**/*',
            dest: 'firmware',
          },
        ],
      }),
    ],
  };
});
