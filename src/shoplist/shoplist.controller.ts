import { Body, Controller, Post, UseGuards } from '@nestjs/common';
import { CreateShoplistDto } from './dto/create-shoplist.dto';
import { ShoplistService } from './shoplist.service';
import { AuthenticatedGuard } from 'src/auth/authenticated.guard';

@Controller('dashboard')
export class ShoplistController {
  constructor(private readonly shoplistService: ShoplistService) {}

  @UseGuards(AuthenticatedGuard)
  @Post()
  logg() {
    console.log('POST!!!');
  }
}
