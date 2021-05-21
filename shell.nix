#
# $ nix-shell --pure --argstr tag 20.09
#

{
  tag ? "20.09"
}:
let
  pkgs = import (builtins.fetchTarball "https://github.com/NixOS/nixpkgs/archive/${tag}.tar.gz") {};
  pypkgs = pkgs.python3Packages;
  graspi = pypkgs.callPackage ./default.nix {};
  linting = with pypkgs; [ black pylint flake8 ];
in
  (graspi.overridePythonAttrs (old: rec {
    nativeBuildInputs = old.propogatedBuildInputs ++ linting;
    postShellHook = ''
      export OMPI_MCA_plm_rsh_agent=${pkgs.openssh}/bin/ssh

      SOURCE_DATE_EPOCH=$(date +%s)
      export PYTHONUSERBASE=$PWD/.local
      export USER_SITE=`python -c "import site; print(site.USER_SITE)"`
      export PYTHONPATH=$PYTHONPATH:$USER_SITE
      export PATH=$PATH:$PYTHONUSERBASE/bin

    '';
  }))
