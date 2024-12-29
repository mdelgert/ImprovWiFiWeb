// import { defineConfig } from 'vite';

// export default defineConfig(({ command }) => ({
//   root: 'public',
//   build: {
//     outDir: '../dist',
//     emptyOutDir: true,
//   },
//   base: command === 'serve' ? '/' : '/ImprovWiFiWeb/', // Use '/' for local dev and '/ImprovWiFiWeb/' for production
// }));

import { defineConfig } from 'vite';

export default defineConfig(({ mode }) => {
  const isGitHubPages = process.env.GITHUB_REPOSITORY; // Check if it's being built for GitHub Pages
  const basePath = isGitHubPages ? `/${process.env.GITHUB_REPOSITORY.split('/')[1]}/` : '/';

  return {
    root: 'public', // Specify "public" as the development root
    build: {
      base: basePath, // Use GitHub Pages repository path or root for local development
      outDir: '../dist', // Ensure the build output is placed in "website/dist"
      emptyOutDir: true, // Clean the output directory before building
    },
  };
});



