import { defineConfig } from 'vite';

export default defineConfig(({ command }) => ({
  root: 'public',
  build: {
    outDir: '../dist',
    emptyOutDir: true,
  },
  base: command === 'serve' ? '/' : '/ImprovWiFiWeb/', // Use '/' for local dev and '/ImprovWiFiWeb/' for production
}));
