let countriesUrl = "https://gist.githubusercontent.com/rusty-key/659db3f4566df459bd59c8a53dc9f71f/raw/4127f9550ef063121c564025f6d27dceeb279623/counties.json";

type request;
type response;

[@bs.new] external makeXMLHttpRequest: unit => request = "XMLHttpRequest";

[@bs.scope "JSON"] [@bs.val]
external parseResponse: response => array(Country.t) = "parse";

[@bs.send]
external addEventListener: (request, string, unit => unit) => unit =
  "addEventListener";
[@bs.get] external response: request => response = "response";
[@bs.send] external open_: (request, string, string) => unit = "open";
[@bs.send] external send: request => unit = "send";
[@bs.send] external abort: request => unit = "abort";

let getCountries = (request, cbOnLoad) => {
  request->addEventListener("load", () => {
    let response = request->response->parseResponse;
    cbOnLoad(response);
  });
  request->open_("GET", countriesUrl);
  request->send;
};
