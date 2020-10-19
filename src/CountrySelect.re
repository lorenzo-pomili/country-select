type state =
  | Loading
  | Error
  | Loaded(array(Country.t));

[@react.component]
let make = (~_className, ~_country, ~_onChange) => {
  let (countries, setCountries) = React.useState(() => Loading);
  React.useEffect0(() => {
    let request = GetData.makeXMLHttpRequest();
    GetData.getCountries(request, cs => setCountries(_prev => Loaded(cs)));
    Some(() => {GetData.abort(request)});
  });

  <div>
    {switch (countries) {
     | Loading => <div> "Loading..."->React.string </div>
     | Error => <div> "Error"->React.string </div>
     | Loaded(cs) =>
       <ReactSelect
         defaultValue=None
         isDisabled=false
         isLoading=false
         isClearable=true
         isRtl=true
         isSearchable=true
         name="test"
         options={cs->Belt.Array.map(ReactSelect.optFromCountry)}
       />
     }}
  </div>;
};

// {cs
//  ->Belt.Array.map(c =>
//      <div key={c.value}>
//        <CountryFlag countryCode={c.value} />
//        {c.label}->React.string
//      </div>
//    )-> React.array}
