open Jest;

open Expect;

open Colorable;

describe(
  "hsl to rgb",
  () => {
    test("1", () => expect(fromHsl((322., 100., 50.))) |> toEqual(fromRgb((255, 0, 161))));
    test("2", () => expect(fromHsl((62., 100., 50.))) |> toEqual(fromRgb((246, 255, 0))));
    ()
  }
);

describe(
  "manipulation",
  () => {
    test(
      "lighten",
      () =>
        expect(
          {
            let (_, _, l) = fromHsl((100., 50., 60.)) |> lighten(0.5) |> toHsl;
            l
          }
        )
        |> toEqual(90.)
    );
    test(
      "darken",
      () =>
        expect(
          {
            let (_, _, l) = fromHsl((100., 50., 60.)) |> darken(0.5) |> toHsl;
            l
          }
        )
        |> toEqual(30.)
    );
    test(
      "saturate",
      () =>
        expect(
          {
            let (_, s, _) = fromHsl((100., 40., 50.)) |> saturate(0.5) |> toHsl;
            s
          }
        )
        |> toEqual(60.)
    );
    test(
      "desaturate",
      () =>
        expect(
          {
            let (_, s, _) = fromHsl((100., 80., 60.)) |> desaturate(0.5) |> toHsl;
            s
          }
        )
        |> toEqual(40.)
    );
    test(
      "rotate +",
      () =>
        expect(
          {
            let (h, _, _) = fromHsl((60., 0., 0.)) |> rotate(180.) |> toHsl;
            h
          }
        )
        |> toEqual(240.)
    );
    test(
      "rotate -",
      () =>
        expect(
          {
            let (h, _, _) = fromHsl((60., 0., 0.)) |> rotate((-180.)) |> toHsl;
            h
          }
        )
        |> toEqual(240.)
    );
    test(
      "intergration 1",
      () =>
        expect(fromHsl((192., 100., 50.)) |> rotate(130.) |> saturate(0.) |> lighten(0.))
        |> toEqual(fromHsl((322., 100., 50.)))
    );
    test(
      "intergration 2",
      () =>
        expect(fromHsl((192., 100., 50.)) |> saturate(1.) |> lighten(0.))
        |> toEqual(fromHsl((192., 100., 50.)))
    );
    ()
  }
);