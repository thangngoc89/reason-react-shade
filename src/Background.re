let component = ReasonReact.statelessComponent("Background");

let make = (~gradient: string, ~light: bool, ~appInfo, _children) => {
  ...component,
  render: (_self) => {
    let backgroundStyle =
      ReactDOMRe.Style.make(
        ~color=light ? "black" : "white",
        ~backgroundImage=gradient,
        ~minHeight="80vh",
        ()
      );
    let preClass = "h5 right-align p1 m0 " ++ (light ? "black" : "white");
    <div style=backgroundStyle className="flex flex-column">
      <div className="p3"> <Header appInfo /> </div>
      <div className="flex-auto" />
      <pre className=preClass> (Utils.strEl("background-image: " ++ gradient ++ ";")) </pre>
    </div>
  }
};