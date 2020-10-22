[@react.component]
let make = () =>
  <div>
    <CountrySelect
      _className="custom-class"
      country={Some("us")}
      _onChange={country => Js.log(country)}
    />
  </div>;
