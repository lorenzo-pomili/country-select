type optionValue = string;

type opt = {
  value: optionValue,
  label: string,
};

module Option = {
  type cx;
  type getStyles;
  type innerProps;
  type theme;
  type selectProps;
  type setValue;
  type clearValue;
  type getValue;
  type options;
  type selectOption;

  type optionProps = {
    children: React.element,
    label: string,
    className: string,
    cx,
    getStyles,
    data: opt,
    isDisabled: bool,
    isFocused: bool,
    isSelected: bool,
    hasValue: bool,
    isMulti: bool,
    isRtl: bool,
    value: optionValue,
    innerRef: React.ref(React.element),
    innerProps,
    setValue,
    selectProps,
    theme,
    clearValue,
    getValue,
    options,
    selectOption,
    [@bs.as "type"]
    _type: string,
  };

  [@bs.module "react-select"] [@bs.scope "components"] [@bs.val]
  external make: optionProps => React.element = "Option";
};

type components = {
  [@bs.as "Option"]
  opt: Option.optionProps => React.element,
};

let optFromCountry = (o: Country.t): opt => {value: o.value, label: o.label};

[@bs.module "react-select"] [@react.component]
external make:
  (
    ~defaultValue: option(opt),
    ~components: components,
    ~isDisabled: bool,
    ~isLoading: bool,
    ~isClearable: bool,
    ~isRtl: bool,
    ~isSearchable: bool,
    ~name: string,
    ~filterOption: (opt, string) => bool,
    ~options: array(opt)
  ) =>
  React.element =
  "default";
