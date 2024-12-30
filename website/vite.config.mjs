import { defineConfig } from 'vite';
import { viteStaticCopy } from 'vite-plugin-static-copy';

export default defineConfig({
  root: 'public',
  build: {
    outDir: '../dist',
    emptyOutDir: true,
  },
  plugins: [
    viteStaticCopy({
      targets: [
        {
          src: 'firmware/**/*', // Copy everything in public/firmware
          dest: 'firmware', // Place it in dist/firmware
        },
      ],
    }),
  ],
});
