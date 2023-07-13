import { Module } from '@nestjs/common';
import { APP_GUARD } from '@nestjs/core';
import { MongooseModule } from '@nestjs/mongoose';
import { RateLimiterGuard, RateLimiterModule } from 'nestjs-rate-limiter';
import { UserModule } from 'src/user/user.module';
import { Shoplist, ShoplistSchema } from './schema/shoplist.schema';
import { ShoplistController } from './shoplist.controller';
import { ShoplistService } from './shoplist.service';
@Module({
  imports: [
    UserModule,
    RateLimiterModule.register({
      points: 5,
      duration: 60,
    }),
    MongooseModule.forFeature([
      { name: Shoplist.name, schema: ShoplistSchema },
    ]),
  ],
  controllers: [ShoplistController],
  providers: [
    ShoplistService,
    { provide: APP_GUARD, useClass: RateLimiterGuard },
  ],
})
export class ShoplistModule {}
