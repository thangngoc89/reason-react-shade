open Jest;

open Expect;

open Colorable;

describe(
  "hsl to rgb",
  () => {
    test(
      "1",
      () =>
        expect(Converter.fromHsl((322., 100., 50.))) |> toEqual(Converter.fromRgb((255, 0, 161)))
    );
    test(
      "2",
      () =>
        expect(Converter.fromHsl((62., 120., 50.))) |> toEqual(Converter.fromRgb((255, 0, 161)))
    );
    ()
  }
);