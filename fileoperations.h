struct file_operations fops =
{
	open : Opendev,
	release: Releasedev,
	write: Writedev
};
