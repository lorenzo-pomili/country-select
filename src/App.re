[@react.component]
let make = () =>
  <div>
    <CountrySelect
      className="custom-class"
      country={Some("us")}
      onChange={country => Js.log(country)}
    />
  </div>;
