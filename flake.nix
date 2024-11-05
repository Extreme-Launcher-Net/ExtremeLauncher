{
  description = "A custom launcher for Minecraft that allows you to easily manage multiple installations of Minecraft at once (Fork of MultiMC)";

  nixConfig = {
    extra-substituters = [ "https://extremelauncher.cachix.org" ];
    extra-trusted-public-keys = [
      "extremelauncher.cachix.org-1:U9Kycn4CKXn/LcEW67OiQ7Wr/INyEw5IXqghMWeu9uw="
    ];
  };

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

    libnbtplusplus = {
      url = "github:Extreme-Launcher/libnbtplusplus";
      flake = false;
    };

    nix-filter.url = "github:numtide/nix-filter";

    /*
      Inputs below this are optional and can be removed

      ```
      {
        inputs.extremelauncher = {
          url = "github:Extreme-Launcher/Extreme-Launcher";
          inputs = {
      	    flake-compat.follows = "";
          };
        };
      }
      ```
    */

    flake-compat = {
      url = "github:edolstra/flake-compat";
      flake = false;
    };
  };

  outputs =
    {
      self,
      nixpkgs,
      libnbtplusplus,
      nix-filter,
      ...
    }:
    let
      inherit (nixpkgs) lib;

      # While we only officially support aarch and x86_64 on Linux and MacOS,
      # we expose a reasonable amount of other systems for users who want to
      # build for most exotic platforms
      systems = lib.systems.flakeExposed;

      forAllSystems = lib.genAttrs systems;
      nixpkgsFor = forAllSystems (system: nixpkgs.legacyPackages.${system});
    in
    {
      checks = forAllSystems (
        system:
        let
          checks' = nixpkgsFor.${system}.callPackage ./nix/checks.nix { inherit self; };
        in
        lib.filterAttrs (_: lib.isDerivation) checks'
      );

      devShells = forAllSystems (
        system:
        let
          pkgs = nixpkgsFor.${system};
        in
        {
          default = pkgs.mkShell {
            inputsFrom = [ self.packages.${system}.extremelauncher-unwrapped ];
            buildInputs = with pkgs; [
              ccache
              ninja
            ];
          };
        }
      );

      formatter = forAllSystems (system: nixpkgsFor.${system}.nixfmt-rfc-style);

      overlays.default = final: prev: {
        extremelauncher-unwrapped = prev.callPackage ./nix/unwrapped.nix {
          inherit
            libnbtplusplus
            nix-filter
            self
            ;
        };

        extremelauncher = final.callPackage ./nix/wrapper.nix { };
      };

      packages = forAllSystems (
        system:
        let
          pkgs = nixpkgsFor.${system};

          # Build a scope from our overlay
          extremePackages = lib.makeScope pkgs.newScope (final: self.overlays.default final pkgs);

          # Grab our packages from it and set the default
          packages = {
            inherit (extremePackages) extremelauncher-unwrapped extremelauncher;
            default = extremePackages.extremelauncher;
          };
        in
        # Only output them if they're available on the current system
        lib.filterAttrs (_: lib.meta.availableOn pkgs.stdenv.hostPlatform) packages
      );

      # We put these under legacyPackages as they are meant for CI, not end user consumption
      legacyPackages = forAllSystems (
        system:
        let
          extremePackages = self.packages.${system};
          legacyPackages = self.legacyPackages.${system};
        in
        {
          extremelauncher-debug = extremePackages.extremelauncher.override {
            extremelauncher-unwrapped = legacyPackages.extremelauncher-unwrapped-debug;
          };

          extremelauncher-unwrapped-debug = extremePackages.extremelauncher-unwrapped.overrideAttrs {
            cmakeBuildType = "Debug";
            dontStrip = true;
          };
        }
      );
    };
}
