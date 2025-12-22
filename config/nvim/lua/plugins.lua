local lazypath=vim.fn.stdpath("data").."/lazy/lazy.nvim"
if not vim.loop.fs_stat(lazypath) then
  vim.fn.system({"git","clone","https://github.com/folke/lazy.nvim.git",lazypath})
end
vim.opt.rtp:prepend(lazypath)
require("lazy").setup({
 {"nvim-treesitter/nvim-treesitter",build=":TSUpdate"},
 {"neovim/nvim-lspconfig"},
 {"williamboman/mason.nvim"},
 {"williamboman/mason-lspconfig.nvim"},
 {"nvim-telescope/telescope.nvim",dependencies={"nvim-lua/plenary.nvim"}},
})
