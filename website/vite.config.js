import { defineConfig } from 'vite';

export default defineConfig(({ command }) => {
  const isProduction = command === 'build';
  const basePath = isProduction ? '/ImprovWiFiWeb/' : '/'; // Use the correct base path for GitHub Pages

  return {
    root: 'public',
    build: {
      outDir: '../dist',
      emptyOutDir: true,
    },
    base: basePath,
  };
});
