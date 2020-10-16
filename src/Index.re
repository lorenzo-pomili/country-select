[@bs.scope "document"] [@bs.val]
external getElementById: string => Dom.element = "getElementById";

ReactDOMRe.render(<App />, getElementById("root"));
