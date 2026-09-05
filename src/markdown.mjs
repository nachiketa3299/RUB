// Keep authored Markdown portable; add the deployment prefix only when rendering.
export function markdown({ base }) {
  return (tree) => {
    const visit = (node) => {
      if (node.url?.startsWith('/') && !node.url.startsWith('//')) {
        node.url = `${base}${node.url}`;
      }
      if (node.type === 'html') {
        node.value = node.value.replace(/((?:href|src)=["'])\/(?!\/)/g, `$1${base}/`);
      }
      if (node.type === 'code' && node.lang === 'plantuml') {
        const source = Buffer.from(node.value).toString('hex');
        node.type = 'image';
        node.url = `https://www.plantuml.com/plantuml/svg/~h${source}`;
        node.alt = 'PlantUML 다이어그램';
        delete node.lang;
        delete node.value;
      }
      node.children?.forEach(visit);
    };
    visit(tree);
  };
}
