type state =
  | Loading
  | Error
  | Loaded(array(Country.t));

let filterOption = (candidate: ReactSelect.opt, input) =>
  input !== ""
    ? Js.String.toLowerCase(input)
      ->Js.String.includes(Js.String.toLowerCase(candidate.label))
    : true;

let maxRenderedItems = 35;

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
         components={
           opt: props =>
             ReactSelect.Option.make({
               ...props,
               children:
                 <CountryFlag countryCode={props.value}>
                   {props.children}
                 </CountryFlag>,
             }),
           menuList: props => {
             let selectedValues = props.getValue();
             let initialOffset =
               switch (selectedValues) {
               | None => 0
               | Some(opts) =>
                 props.options
                 ->Belt.Array.getIndexBy(o =>
                     switch (opts->Belt.Array.get(0)) {
                     | None => false
                     | Some(o2) => o2.value === o.value
                     }
                   )
                 ->Belt.Option.getWithDefault(0)
                 * maxRenderedItems
               };
             <FixedSizeList
               itemSize=maxRenderedItems
               height={props.maxHeight}
               itemCount={props.children->Belt.Array.length}
               initialScrollOffset=initialOffset>
               (
                 ({style, index}) => {
                   <div style>
                     {switch (props.children->Belt.Array.get(index)) {
                      | None => React.null
                      | Some(e) => e
                      }}
                   </div>;
                 }
               )
             </FixedSizeList>;
           },
         }
         isDisabled=false
         isLoading=false
         isClearable=false
         isRtl=false
         isSearchable=true
         filterOption
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
