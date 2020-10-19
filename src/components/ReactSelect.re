type opt = {
  value: string,
  label: string,
};

let optFromCountry = (o: Country.t): opt => {value: o.value, label: o.label};

[@bs.module "react-select"] [@react.component]
external make:
  (
    ~defaultValue: option(opt),
    ~isDisabled: bool,
    ~isLoading: bool,
    ~isClearable: bool,
    ~isRtl: bool,
    ~isSearchable: bool,
    ~name: string,
    ~options: array(opt)
  ) =>
  React.element =
  "default";
