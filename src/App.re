[@react.component]
let make = () =>
  <div>
    <CountrySelect
      _className="custom-class"
      country={Some("us")}
      onChange={country => Js.log(country)}
    />
  </div>;
