#!/usr/bin/env npx tsx

import { glob, readFile, writeFile } from "node:fs/promises";

const markdownFiles = (
  await Promise.all(
    (await Array.fromAsync(glob(["README.md", "Documentation/**/*.md"]))).map(
      async (path) => {
        return [path, await readFile(path, "utf8")];
      },
    ),
  )
).reduce((prev, [key, value]) => ({ ...prev, [key]: value }), {}) as {
  [key: string]: string;
};

const sourceFiles = (
  await Promise.all(
    (
      await Array.fromAsync(
        glob(["Documentation/**/*.cpp", "Documentation/**/*.cs"]),
      )
    ).map(async (path) => {
      return [path, await readFile(path, "utf8")];
    }),
  )
).reduce((prev, [key, value]) => ({ ...prev, [key]: value }), {}) as {
  [key: string]: string;
};

for (let [markdownPath, markdownContents] of Object.entries(markdownFiles)) {
  for (const [path, contents] of Object.entries(sourceFiles)) {
    const pattern = new RegExp(`// ${path}.+?([\`]{3})`, "ms");

    const matches = markdownContents.match(pattern);

    if (matches) {
      console.log(`Replacing code snippet in ${markdownPath} for ${path}`);

      markdownContents = markdownContents.replace(
        pattern,
        `// ${path}\n${contents.trim()}\n\`\`\``,
      );

      await writeFile(markdownPath, markdownContents);
    }
  }
}
