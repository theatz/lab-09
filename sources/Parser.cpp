//
// Created by mrbgn on 4/5/21.
//

#include <Parser.hpp>

Parser::Parser(std::size_t depth) : _depth(depth){};

void Parser::SearchForLinks(GumboNode* node, PageOutput& pageOutput) {
  if (node->type != GUMBO_NODE_ELEMENT) {
    return;
  }
  GumboAttribute* href;

  if (node->v.element.tag == GUMBO_TAG_A &&
      (href = gumbo_get_attribute(&node->v.element.attributes, "href"))) {
    if (DefineLink(href->value)) {
      std::string push = href->value;
      pageOutput.url.push_back(UrlToDownload{push.substr(7), pageOutput.url[0].depth + 1}); // todo
    }
  }

  GumboAttribute* src;
  if (node->v.element.tag == GUMBO_TAG_IMG &&
      (src = gumbo_get_attribute(&node->v.element.attributes, "src"))) {
    if (DefineLink(src->value)) {
      std::string push = src->value;
      pageOutput.src.push_back(push.substr(7));
    }
  }

  GumboVector* children = &node->v.element.children;
  for (unsigned int i = 0; i < children->length; ++i) {
    SearchForLinks(static_cast<GumboNode*>(children->data[i]), pageOutput);
  }
}
PageOutput Parser::Parse(PageToParse page) {
  struct PageOutput pageOutput;
  pageOutput.url.clear();
  pageOutput.src.clear();

  GumboOutput* output = gumbo_parse(page.page.c_str());
  SearchForLinks(output->root, pageOutput);
  gumbo_destroy_output(&kGumboDefaultOptions, output);

  return pageOutput;
}
bool Parser::DefineLink(std::string link) {
  std::size_t found;
  found = link.find("htpps://");
  if (found != std::string::npos) return false;
  found = link.find("http://");
  if (found == std::string::npos) return false;
  return true;
}
